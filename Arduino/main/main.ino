#include <ChainableLED.h>
#include <rpcWiFi.h>
#include <PubSubClient.h>
#include "LIS3DHTR.h"
#include "AccelerometerSensor.h"
#include "TemperatureSensor.h"
#include "CarController.h"
#include "BrakeLight.h"

LIS3DHTR<TwoWire> lis;

// Update these with values suitable for your network:
const char *ssid = "Parham";      // network SSID (Wifi)
const char *password = "Parham3000"; // your network password

const char *ID = "Wio-Terminal-Client-meep";  // Name of our device, must be unique
// c172.20.10.3 - local brocker
// broker.hivemq.com
// test.mosquitto.org
const char *server = "broker.hivemq.com"; // ONLINE SERVER
const uint16_t port = 1883;

const int leftForward = D0;
const int leftBackward = D1;
const int rightForward = D3;
const int rightBackward = D2;


String sub_topics[5] = { 
  "carduino/lcd/print",
  "carduino/buzzer",
  "carduino/movement",
  "carduino/light",
  "carduino/power/off",
};

const char* speedTopic = "carduino/accelerometer/speed";
const char* distanceTopic = "carduino/accelerometer/distance";
const char* temperatureTopic = "carduino/temperature";
const char* brakeTopic = "carduino/light";

// For turning off
bool running = true;

// Brake Light turning on
bool enabled = true;

// For Update Frequency
double systemTime;
double previousTime = millis();
double updateIntervalMs = 1000;
double deltaTime = 0;

// TFT_eSPI lcd; // WIO LCD Display

#define BUZZER_PIN WIO_BUZZER // WIO Buzzer
#define LCD_BACKLIGHT (72Ul) // Control Pin of LCD

WiFiClient wifiClient;
PubSubClient client(wifiClient);
AccelerometerSensor accelerometer(client, speedTopic);
TemperatureSensor temperatureSensor(client, temperatureTopic);
BrakeLight brakeLight;
CarController wheels(brakeLight);

// setup() and loop() are the main methods for the Arduino
// setup() runs once
void setup()
{ 
  
  // to turn on WIO LCD
  //lcd.begin();
  //lcd.setRotation(3);
  //lcd.fillScreen(TFT_BLACK);

  // turn on Buzzer
  pinMode(BUZZER_PIN, OUTPUT);

  Serial.begin(115200);
  while (!Serial); // Wait for Serial to be ready
  Serial.print("Attempting to connect to SSID(network): "); 
  Serial.println(ssid);
  WiFi.begin(ssid, password); //initiate Wifi connection

  // attempt to connect to Wifi network:
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    WiFi.begin(ssid, password);
    delay(1000); // wait 1 second for re-trying
  }
  Serial.print("Connected to ");
  Serial.println(ssid);
  delay(500);

  client.setServer(server, port);
  client.setCallback(callback);
  client.subscribe(brakeTopic);
  accelerometer.setup();
  temperatureSensor.setup();
  wheels.setup();
  brakeLight.setup();
}

// loop() runs forever
void loop()
{

  // reconnect if connection failed
  if (!client.connected()) {
    reconnect();
  }

  // Timer functionality
  systemTime = millis();
  deltaTime += (systemTime - previousTime) / updateIntervalMs;
  previousTime = systemTime;

  // MQTT Updates should be done inside this if statement to avoid publishing to the different topics too often.
  if (deltaTime >= 1){

    deltaTime --;

    accelerometer.publishMQTT(accelerometer.getSensorValue());
    temperatureSensor.publishMQTT(temperatureSensor.getSensorValue());

    // Need to add a function to check if the car is moving or not to restart the speed since it only accumulates...
    accelerometer.publishMQTT(distanceTopic,accelerometer.getTravelledDistance());
  }

  client.loop();
}

void reconnect() {
  while (!client.connected()) // Loop until we reconnected
  {
    Serial.print("Attempting MQTT connection...");
    // Connect:
    if (client.connect(ID)) {
      Serial.println("connected");
      // Publish
      // client.publish("", "{\"message\": \"Wio Terminal is connected!\"}");
      // Serial.println("Published connection message successfully!");
      // Subscribe
      for(String topic : sub_topics){
         client.subscribe(topic.c_str());
      }
      // client.subscribe("carduino/lcd/print");
      // client.subscribe("carduino/buzzer/honk");
      // client.subscribe("carduino/directions/live-control");
      // client.subscribe("carduino/power/off");
      Serial.println("Subcribed to all topics");
    }
    else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

// The callback function must be provided for PubSubClient (if we subscribe).
// This function is called when new messages arrive at the client. 
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  // Assign recieved payload to a String (message): 
  String message = "";
  for (int i=0;i<length;i++) { 
    Serial.print((char)payload[i]);
    message.concat((char)payload[i]);
  }
  Serial.println();

  reciever_actions(topic, message);
}

void reciever_actions(String topic, String message){
  // Honk
  if (topic == "carduino/buzzer"){
    if (message == "honk") honk(0); //pass message as option
    if (message == "tune") honk(1); //pass message as option
    if (message == "anthem") honk(2); //pass message as option
  }

  // Print to WIO screen
  if (topic == "carduino/lcd/print"){
      // String text = "";
      // text.concat(message);
      // print_to_WIO(text);
  }

  if (topic == "carduino/movement"){
     wheels.wheelsReceiver(message);
    
  }

  if (topic == "carduino/light"){
    brakeLight.lightReceiver(message);
  
  }

  if (topic == "carduino/power/off"){
    
    if (message == "12345678Sivert") running = false;

  }
}

/* Methods for WIO Terminal */

void print_to_WIO(String message){
  // lcd.fillScreen(TFT_BLACK);
  // lcd.setTextSize(2);
  // lcd.drawString(message, 0, 10);
}

char notes_tune[] = "ccggaagffeeddc ";
int beats_tune[] = { 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4 };
char notes_anthem[] = "ggecg edc ggecg fed ";
int beats_anthem[] = {2,2,2,1,1,4, 2,2,4, 2,2,2,1,1,4, 2,2,4, 4};
int tempo = 200;


void honk(int option){
  switch(option){
    case 0: // honk
      playTone(1519,1000);
      break;
    case 1: // tune
      readMusicSheet(notes_tune, beats_tune, 15);
      break;
    case 2: // anthem
      readMusicSheet(notes_anthem, beats_anthem, 19);
      break;
    default: Serial.println("waa");
  }
}

void readMusicSheet(char notes[], int beats[], int length) {
  for(int i = 0; i < length; i++) {
    if(notes[i] == ' ') {
        delay(beats[i] * tempo);
    } else {
        playNote(notes[i], beats[i] * tempo);
    }
    delay(tempo / 2); //delay between notes 
  }
  return;
}

void playNote(char note, int duration) {
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };

  // play the tone corresponding to the note name
  for (int i = 0; i < 8; i++) {
    if (names[i] == note) {
      playTone(tones[i], duration);
    }
  }
}

void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(BUZZER_PIN, HIGH);
    delayMicroseconds(tone);
    digitalWrite(BUZZER_PIN, LOW);
    delayMicroseconds(tone);
  }
}



#include <rpcWiFi.h>
#include <PubSubClient.h>
#include "LIS3DHTR.h"
#include "AccelerometerSensor.h"
#include "TemperatureSensor.h"

LIS3DHTR<TwoWire> lis;
#include"LIS3DHTR.h" // Timer

// Update these with values suitable for your network:
const char *ssid = "PW-Tech-2.4Ghz";      // network SSID (Wifi)
const char *password = "Parham3000"; // your network password

const char *ID = "Wio-Terminal-Client-meep";  // Name of our device, must be unique
const char *pubTOPIC = "my/test/topic";  // Topic to publish to
const char *subTopic = "my/test/topic";  // Topic to subcribe to
const char *accelerometerTopic = "carduino/acceleration";
const char *server = "test.mosquitto.org"; // Address of brocker (URL or IP)

// For Update Frequency
double systemTime;
double previousTime = millis();
double updateIntervalMs = 1000;
double deltaTime = 0;


#define BUZZER_PIN WIO_BUZZER // WIO Buzzer
#define LCD_BACKLIGHT (72Ul) // Control Pin of LCD

WiFiClient wifiClient;
PubSubClient client(wifiClient);
AccelerometerSensor accelerometer(client,accelerometerTopic);

void reconnect() {
  
  while (!client.connected()) // Loop until we reconnected
  {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect:
    if (client.connect(ID)) {
      Serial.println("connected");
      client.publish(accelerometerTopic, "{\"message\": \"Wio Terminal is connected!\"}");
      Serial.println("Published connection message successfully!");
      
    }
    else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
 
}

// setup() and loop() are the main methods for the Arduino
// setup() runs once
void setup()
{ 
  
  // to turn on WIO LCD
  lcd.begin();
  lcd.setRotation(3);
  lcd.fillScreen(TFT_BLACK);

  

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
  accelerometer.setup();
  temperatureSensor.setup();
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

  if (topic == "carduino/directions/live-control"){
    
    //draw arrows
    
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



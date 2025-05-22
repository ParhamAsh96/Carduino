#include <ChainableLED.h>
#include <rpcWiFi.h>
#include <PubSubClient.h>
#include "LIS3DHTR.h"
#include "AccelerometerSensor.h"
#include "TemperatureSensor.h"
#include "CarController.h"
#include "BrakeLight.h"
#include "Tunes.h"

#define RESET_TURN_OFF 300;

LIS3DHTR<TwoWire> lis;

// Update these with values suitable for your network:
const char *ssid = "iPhoneiee♨️";      // network SSID (Wifi)
const char *password = "14444444"; // your network password

const char *ID = "Wio-Terminal-Client-meep";  // Name of our device, must be unique
// 172.20.10.3 - local brocker
// broker.hivemq.com
// test.mosquitto.org
const char *server = "broker.hivemq.com";
const uint16_t port = 1883;

String sub_topics[4] = { 
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
double turnOffTimer = RESET_TURN_OFF;
bool stopLoop = false;

// For Update Frequency
double systemTime;
double previousTime = millis();
double updateIntervalMs = 1000;
double deltaTime = 0;

// To check topics and messages inside other methods
String recTopic = " ";
String recMsg = " ";

WiFiClient wifiClient;
PubSubClient client(wifiClient);
AccelerometerSensor accelerometer(client, speedTopic);
TemperatureSensor temperatureSensor(client, temperatureTopic);
BrakeLight brakeLight;
CarController wheels(brakeLight);
Tunes tunes(&client, &recTopic);

// setup() and loop() are the main methods for the Arduino
// setup() runs once
void setup()
{ 

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
  tunes.setup();
}

// loop() runs forever
void loop()
{
  if(!stopLoop) {
    
    // reconnect if connection failed
    if (!client.connected()) {
      reconnect();
    }

    // Timer functionality
    systemTime = millis();
    deltaTime += (systemTime - previousTime) / updateIntervalMs;
    previousTime = systemTime;

    /* this if-statememnt runs every 1000 ms */
    if (deltaTime >= 1){

      deltaTime --;
      turnOffTimer--;

      accelerometer.publishMQTT(accelerometer.getSensorValue());
      temperatureSensor.publishMQTT(temperatureSensor.getSensorValue());

      // Need to add a function to check if the car is moving or not to restart the speed since it only accumulates...
      accelerometer.publishMQTT(distanceTopic,accelerometer.getTravelledDistance());
    }

    if (client.connected()){
      client.loop();
    }

    // turn off the car
  if(!running || turnOffTimer <= 1) turnCarduinoOff();
  }//stopLoop
}

void reconnect() {
  while (!client.connected()) // Loop until we reconnected
  {
    Serial.print("Attempting MQTT connection...");
    // Connect
    if (client.connect(ID)) {
      Serial.println("connected");
      // Publish
      // client.publish("", "{\"message\": \"Wio Terminal is connected!\"}");
      // Serial.println("Published connection message successfully!");
      // Subscribe
      for(String topic : sub_topics){
         client.subscribe(topic.c_str());
      }
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

// The callback function is set with "client.setCallback(callback);" .
// This function is called when new messages arrive at the client. 
void callback(char* topic, byte* payload, unsigned int length) {
  turnOffTimer = RESET_TURN_OFF; // Auto-Turn-Off timer resets each time we recieve a message
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

  setRecTopic(topic);
  setMessage(message);

  //IMPORTANT, prevents unnecessary recursion
  if (!tunes.checkWheels()) reciever_actions(topic, message);
}

void setRecTopic(String topic){
  recTopic = topic;
}

void setMessage(String msg){
  recMsg = msg;
}

void reciever_actions(String topic, String message){
  // Honk
  if (topic == "carduino/buzzer"){
    tunes.tuneReceiver(message);
    wheels.wheelsReceiver(recMsg); // runs only when mqtt for wheels is recieved while the buzzer plays
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

void turnCarduinoOff(){
  digitalWrite(2, LOW);// temperatureSensor.
  digitalWrite(6, LOW);// wheels.
  digitalWrite(5, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(1, LOW); // brakeLight. CLK_PIN(A0), DAT_PIN(A1)
  digitalWrite(0, LOW); // brakeLight. CLK_PIN(A0), DAT_PIN(A1)
  digitalWrite(3, LOW); 
  digitalWrite(4, LOW); 
  pinMode(A0, LOW);
  pinMode(A2, LOW);
  brakeLight.brakeLightOff();
  stopLoop = true;
  client.disconnect();
}

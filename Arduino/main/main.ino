#include <TFT_eSPI.h>
#include <rpcWiFi.h>
#include <PubSubClient.h>
#include"LIS3DHTR.h"
LIS3DHTR<TwoWire> lis;

// Update these with values suitable for your network:
const char *ssid = "Test";      // network SSID (Wifi)
const char *password = "abcdefghi"; // your network password

const char *ID = "Wio-Terminal-Client-meep";  // Name of our device, must be unique
const char *pubTOPIC = "my/test/topic";  // Topic to publish to
const char *subTopic = "my/test/topic";  // Topic to subcribe to
const char *server = "192.168.189.16"; // Address of brocker (URL or IP)

// For Update Frequency
double systemTime;
double previousTime = millis();
double updateIntervalMs = 1000;
double deltaTime = 0;


TFT_eSPI lcd;

WiFiClient wifiClient;
PubSubClient client(wifiClient);

void reconnect() {
  
  while (!client.connected()) // Loop until we reconnected
  {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect:
    if (client.connect(ID)) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish(pubTOPIC, "{\"message\": \"Wio Terminal is connected!\"}");
      Serial.println("Published connection message successfully!");
      // ... and resubscribe
      client.subscribe(subTopic);
      Serial.print("Subcribed to: ");
      Serial.println(subTopic);
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

  accelerometerSetup();

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

  client.setServer(server, 1883);
  client.setCallback(callback);
}

// loop() runs forever
void loop()
{
  if (!client.connected()) {
    reconnect();
  }


  systemTime = millis();

  deltaTime += (systemTime - previousTime) / updateIntervalMs;
  previousTime = systemTime;


  // MQTT Updates should be done inside this if statement to avoid publishing to the different topics too often.
  if (deltaTime >= 1){
    deltaTime--;
  
  }


  client.loop();

}

// The callback function must be provided in the constructor. (if we subscribe)
// This function is called when new messages arrive at the client. 
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  // prints the recieved payload (message):
  String cString = "";
  for (int i=0;i<length;i++) { 
    Serial.print((char)payload[i]);
    cString.concat((char)payload[i]);
  }
  Serial.println();
  // Print to WIO screen
  lcd.fillScreen(TFT_BLACK);
  lcd.setTextSize(2);
  lcd.drawString(cString, 0, 10);
}
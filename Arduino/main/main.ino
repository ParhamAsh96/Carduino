#include <TFT_eSPI.h>
#include <rpcWiFi.h>
#include <PubSubClient.h>
#include"LIS3DHTR.h"

// Update these with values suitable for your network:
const char *ssid = "iPhoneiee♨️";      // network SSID (Wifi)
const char *password = "14444444"; // your network password

const char *ID = "Wio-Terminal-Client-meep";  // Name of our device, must be unique
// const char *server = "172.20.10.3"; // Address of brocker (URL or IP)
const char *server = "test.mosquitto.org"; // ONLINE SERVER
const uint16_t port = 1883;

// For turning off
bool running = true;
double turnoffTime = 300;

// For Update Frequency
double systemTime;
double previousTime = millis();
double updateIntervalMs = 1000;
double deltaTime = 0;

TFT_eSPI lcd; //WIO LCD Display
LIS3DHTR<TwoWire> lis; //Timer

#define LCD_BACKLIGHT (72Ul) // Control Pin of LCD

WiFiClient wifiClient;
PubSubClient client(wifiClient);

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
}

// loop() runs forever
void loop()
{
  // turn off the car
  if(!running || turnoffTime <= 1){
    digitalWrite(LCD_BACKLIGHT, LOW);
    return;
  }
  
  if (!client.connected()) {
    reconnect();
  }

  systemTime = millis();
  deltaTime += (systemTime - previousTime) / updateIntervalMs;
  previousTime = systemTime;
  // MQTT Updates should be done using a timer to avoid publishing to the different topics too often.
  if (deltaTime >= 1){
    deltaTime--;
    turnoffTime--;
  }

  client.loop();
}

void reconnect() {
  
  while (!client.connected()) // Loop until we reconnected
  {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect:
    if (client.connect(ID)) {
      Serial.println("connected");
      client.subscribe("carduino/lcd/print");
      client.subscribe("carduino/buzzer/honk");
      client.subscribe("carduino/directions/live-control");
      client.subscribe("carduino/power/off");
      Serial.print("Subcribed to all topics.");
    }
    else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
 
}

// The callback function must be provided in the constructor. (if we subscribe)
// This function is called when new messages arrive at the client. 
void callback(char* topic, byte* payload, unsigned int length) {
  turnoffTime = 300;
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
  // Use Buzzer
  if (topic == "carduino/buzzer/honk"){
    
    //make sound
    
  }

  // Print to WIO screen
  if (topic == "carduino/lcd/print"){

    //print to lcd

  }

  if (topic == "carduino/directions/live-control"){
    
    //draw arrows
    
  }

  if (topic == "carduino/power/off"){
    
    if (message == "12345678Sivert") running = false;

  }
}

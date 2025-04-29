#include <TFT_eSPI.h> // LCD Display
#include <rpcWiFi.h>
#include <PubSubClient.h>
#include"LIS3DHTR.h" // Timer

// Update these with values suitable for your network:
const char *ssid = "iPhoneiee♨️";      // network SSID (Wifi)
const char *password = "14444444"; // your network password

const char *ID = "Wio-Terminal-Client-meep";  // Name of our device, must be unique
// const char *server = "172.20.10.3"; // Address of brocker (URL or IP)
const char *server = "test.mosquitto.org"; // ONLINE SERVER
const uint16_t port = 1883;

String sub_topics[4] = { 
  "carduino/lcd/print",
  "carduino/buzzer/honk",
  "carduino/directions/live-control",
  "carduino/power/off"
};

// For turning off
bool running = true;

// For Update Frequency
double systemTime;
double previousTime = millis();
double updateIntervalMs = 1000;
double deltaTime = 0;

TFT_eSPI lcd; // WIO LCD Display
LIS3DHTR<TwoWire> lis; // Timer

#define BUZZER_PIN WIO_BUZZER // WIO Buzzer
#define LCD_BACKLIGHT (72Ul) // Control Pin of LCD

WiFiClient wifiClient;
PubSubClient client(wifiClient);

// setup() and loop() are the main methods for the Arduino
// setup() runs once
void setup()
{ 
  // turn on WIO LCD
  lcd.begin();
  lcd.setRotation(3);
  lcd.fillScreen(TFT_BLACK);

  // turn on Buzzer
  pinMode(WIO_BUZZER, OUTPUT);

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

  // Set MQTT client server connection
  client.setServer(server, port);
  client.setCallback(callback); // set callback function for recieving messages MQTT_sub
}

// loop() runs forever
void loop()
{
  // turn off the car
  if(!running){
    digitalWrite(LCD_BACKLIGHT, LOW);
    return;
  }


  // reconnect if connection failed
  if (!client.connected()) {
    reconnect();
  }

  // Timer functionality
  systemTime = millis();
  deltaTime += (systemTime - previousTime) / updateIntervalMs;
  previousTime = systemTime;
  // MQTT Updates should be done using a timer to avoid publishing to the different topics too often.
  if (deltaTime >= 1){
    deltaTime--;
    
  }
  
  // MQTT client loop to recieve messages 
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
      Serial.println("Published connection message successfully!");
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
  if (topic == "carduino/buzzer/honk"){
    honk(); //pass message as option
  }

  // Print to WIO screen
  if (topic == "carduino/lcd/print"){
      String text = "";
      // text.concat(topic);
      // text.concat(" ");
      text.concat(message);
      print_to_WIO(text);
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
  lcd.fillScreen(TFT_BLACK);
  lcd.setTextSize(2);
  lcd.drawString(message, 0, 10);
}

void honk(){
  analogWrite(WIO_BUZZER, 128);
  delay(1000);
  analogWrite(WIO_BUZZER, 0);
  delay(1000);
}


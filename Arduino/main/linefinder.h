
#include "Arduino.h"
#include "PubSubClient.h"

class LineFinder : public ArduinoSensor{
  public:
    LineFinder(PubSubClient& client, const char* topic, int sensorPin = A0);

    void setup();
    int getSensorValue();
    void publishMQTT();
    void checkForLineAndBrake();

    bool isLineDetected();  // Returns whether the line is detected
    void triggerAutoBrake(bool status);

  

  private:
    int _sensorPin;
    PubSubClient& _client;
    const char* _topic;
    bool _autoBrakeTriggered;
    unsigned long _lastLineLostTime;  //the time when line was last lost

};



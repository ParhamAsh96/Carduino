
#include "Arduino.h"
#include "PubSubClient.h"

class LineFinder{
  public:
    LineFinder(PubSubClient& client, const char* topic, int sensorPin = A0);

    void setup();
    void publishMQTT(int sensorValue);
    void publishMQTT();
    int getSensorValue();

    bool isLineDetected();  // Returns whether the line is detected
    void triggerAutoBrake(bool status);
    void checkAndTriggerAutoBrake(); 


  

  private:
    int _sensorPin;
    PubSubClient& _client;
    const char* _topic;
    bool _autoBrakeTriggered;
    unsigned long _lastLineLostTime;  //the time when line was last lost

};



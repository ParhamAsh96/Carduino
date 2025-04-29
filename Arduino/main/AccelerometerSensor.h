#include "ArduinoSensor.h"
#include "PubSubClient.h"

class AccelerometerSensor : public ArduinoSensor{
public: 

    // Used to read sensor values
    LIS3DHTR<TwoWire> lis;

    // For sensor values
    float xValue, yValue, zValue;
    float totalAcceleration;

    // For calculating changes in speed.
    float arduinoSpeed;
    float previousSpeed;
    float previousTime;
    float currentTime;

    // For turning ms into seconds on speed calculation.
    float msRatio;

    // Pointer to PubSubClient from main and topic
    PubSubClient& client;
    const char *topic;


    // Class functions

    AccelerometerSensor(PubSubClient& client, const char* topic);

    void setup();

    void publishMQTT(float sensorValue) override;
    
    
    float getSensorValue() override;

    ~AccelerometerSensor();

};

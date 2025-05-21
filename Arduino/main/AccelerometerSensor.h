#ifndef ACCELEROMETERSENSOR_H
#define ACCELEROMETERSENSOR_H

#include "LIS3DHTR.h"
#include "ArduinoSensor.h"
#include "PubSubClient.h"

class AccelerometerSensor : public ArduinoSensor{
public: 

    // Class functions

    AccelerometerSensor(PubSubClient& client, const char* topic);

    void setup();

    void calibrateAccelerometer();

    void publishMQTT(float sensorValue) override;

    void publishMQTT(const char* subTopic,float sensorValue);
    
    float getSensorValue() override;

    float getTravelledDistance();
    
    float getXAcceleration();

    float getYAcceleration();

    float getZAcceleration();

    float getTotalAcceleration(float accelerationX, float accelerationY);

    ~AccelerometerSensor();
private:
    
    // Used to read accelerometer values
    LIS3DHTR<TwoWire> lis;

    // For sensor values

    float calibrationX, calibrationY, calibrationZ;

    float accelerationX, accelerationY, accelerationZ;
    float totalAcceleration;

    // For calculating changes in speed.
    float arduinoSpeed;
    float previousSpeed;

    float distanceTravelled;

    // The time variables need to be seperate as the calculations would be wrong since we would get the incorrect delta time for acceleration and speed respectively.
    float previousAccelerationTime;
    float currentAccelerationTime;

    float previousSpeedTime;
    float currentSpeedTime;

    // For turning ms into seconds on speed calculation.
    float msRatio;

    // Pointer to PubSubClient from main and topic
    PubSubClient& client;
    const char *topic;

};

#endif

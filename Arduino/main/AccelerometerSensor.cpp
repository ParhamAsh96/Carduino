#include "LIS3DHTR.h"
#include "PubSubClient.h"
#include "ArduinoSensor.h"
#include "AccelerometerSensor.h"
#include <sstream>

AccelerometerSensor::AccelerometerSensor(PubSubClient& client, const char* topic)
    : client(client), topic(topic) {}

void AccelerometerSensor::setup() {
    lis.begin(Wire1); 
    lis.setOutputDataRate(LIS3DHTR_DATARATE_25HZ); 
    lis.setFullScaleRange(LIS3DHTR_RANGE_2G);

    previousSpeed = 0;
    arduinoSpeed = 0;

    msRatio = 1000;

    distanceTravelled = 0; 

    previousAccelerationTime = millis();

    previousSpeedTime = millis();

}

void AccelerometerSensor::publishMQTT(float sensorValue) {
    char returnMessage[5];
    dtostrf(sensorValue, 0, 2, returnMessage);

    client.publish(topic, returnMessage);
}

void AccelerometerSensor::publishMQTT(const char* subTopic,float sensorValue) {
    char returnMessage[12];
    dtostrf(sensorValue, 0, 2, returnMessage);

    client.publish(subTopic, returnMessage);
}

float AccelerometerSensor::getSensorValue() {


    xValue = lis.getAccelerationX();
    yValue = lis.getAccelerationY();
    /* 
    zValue has some noise and shows 1 less than the actual acceleration. (-1 when standing still) 
    This depends on how the Arduino is positioned and has to be accounted for when placing the arduino in the chassis.
    */
    zValue = lis.getAccelerationZ() + 1;


    // Account for drift in values.
    xValue = (abs(xValue) < 0.07) ? 0 : xValue;
    yValue = (abs(yValue) < 0.07) ? 0 : yValue;
    
    totalAcceleration = sqrt((xValue * xValue) + (yValue * yValue));


    if ((xValue * yValue) < 0 ){
        totalAcceleration = totalAcceleration * -1;
    }

    currentAccelerationTime = millis();
    currentSpeedTime = millis();

    // Assuming constant acceleration in the timeframe.
    arduinoSpeed = previousSpeed + totalAcceleration * (currentAccelerationTime - previousAccelerationTime) / msRatio;
    

    // Distance travelled also needs to be updated in here so we can get the proper speed.
    distanceTravelled += abs(((arduinoSpeed + previousSpeed) / 2) * ((currentSpeedTime - previousSpeedTime) / msRatio));

    previousAccelerationTime = currentSpeedTime;
    previousSpeedTime = currentSpeedTime;
    previousSpeed = arduinoSpeed;

    return arduinoSpeed;
}

float AccelerometerSensor::getTravelledDistance(){

    // Make sure everything is fully updated.
    getSensorValue();

    return distanceTravelled;
    
}

AccelerometerSensor::~AccelerometerSensor() {}
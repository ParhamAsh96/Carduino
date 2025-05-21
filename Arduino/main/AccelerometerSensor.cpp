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

float AccelerometerSensor::getXAcceleration(){
    return lis.getAccelerationX();
}

float AccelerometerSensor::getYAcceleration(){
    return lis.getAccelerationY();
}

float AccelerometerSensor::getTotalAcceleration(float accelerationX, float accelerationY){
    return sqrt((accelerationX * accelerationX) + (accelerationY * accelerationY));
}

float AccelerometerSensor::getSensorValue() {

    accelerationX = getXAcceleration();
    accelerationY = getYAcceleration();

    // Account for drift in values.
    accelerationX = (abs(accelerationX) < 0.07) ? 0 : accelerationX;
    accelerationY = (abs(accelerationY) < 0.07) ? 0 : accelerationY;
    
    totalAcceleration = getTotalAcceleration(accelerationX,accelerationY);


    if ((accelerationX * accelerationY) < 0 ){
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
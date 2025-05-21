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

    calibrationX = 0;
    calibrationY = 0;
    calibrationZ = 0;

    calibrateAccelerometer();
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

void AccelerometerSensor::calibrateAccelerometer(){
    calibrationX = getXAcceleration();
    calibrationY = getYAcceleration();
    calibrationZ = getZAcceleration();
};

float AccelerometerSensor::getXAcceleration(){
    accelerationX = lis.getAccelerationX() - calibrationX;
    accelerationX = (abs(accelerationX) < 0.07) ? 0 : accelerationX;
    return accelerationX;
}

float AccelerometerSensor::getYAcceleration(){
    accelerationY = lis.getAccelerationY() - calibrationY;
    accelerationY = (abs(accelerationY) < 0.07) ? 0 : accelerationY;
    return accelerationY;
}

float AccelerometerSensor::getZAcceleration(){
    accelerationZ = lis.getAccelerationZ() - calibrationZ;
    accelerationZ = (abs(accelerationZ) < 0.07) ? 0 : accelerationZ;
    return accelerationZ;
}

float AccelerometerSensor::getTotalAcceleration(float xAcceleration, float yAcceleration, float zAcceleration){
    return sqrt((xAcceleration * xAcceleration) + (yAcceleration * yAcceleration) + (zAcceleration * zAcceleration));
}

float AccelerometerSensor::getSensorValue() {


    accelerationX = getXAcceleration();
    accelerationY = getYAcceleration();
    accelerationZ = getZAcceleration();

    totalAcceleration = getTotalAcceleration(accelerationX,accelerationY, accelerationZ);

    // Find out if the acceleration is negative (driving backwards)
    if ((accelerationX * accelerationY * accelerationZ) < 0 ){
        totalAcceleration = totalAcceleration * -1;
    }

    arduinoSpeed = updateSpeed(totalAcceleration);

    return arduinoSpeed;
}

float AccelerometerSensor::updateSpeed(float acceleration){
    currentAccelerationTime = millis();
    currentSpeedTime = millis();

    // Assuming constant acceleration in the timeframe.
    arduinoSpeed = previousSpeed + acceleration * (currentAccelerationTime - previousAccelerationTime) / msRatio;
    

    // Distance travelled also needs to be updated in here so we can get the proper speed.
    distanceTravelled += updateDistance();

    previousSpeed = arduinoSpeed;
    previousAccelerationTime = currentSpeedTime;
    previousSpeedTime = currentSpeedTime;
    

    return arduinoSpeed;
}

float AccelerometerSensor::updateDistance(){
    return abs(((arduinoSpeed + previousSpeed) / 2) * ((currentSpeedTime - previousSpeedTime) / msRatio));
}

void AccelerometerSensor::restartSpeed(){
    arduinoSpeed = 0;
}

float AccelerometerSensor::getTravelledDistance(){

    // Make sure everything is fully updated.
    getSensorValue();

    return distanceTravelled;
    
}

AccelerometerSensor::~AccelerometerSensor() {}
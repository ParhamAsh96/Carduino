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

void AccelerometerSensor::calibrateAccelerometer(){
    calibrationX = getXAcceleration();
    calibrationY = getYAcceleration();
    calibrationZ = getZAcceleration();
};

float AccelerometerSensor::getXAcceleration(){
    return lis.getAccelerationX();
}

float AccelerometerSensor::getYAcceleration(){
    return lis.getAccelerationY();
}

float AccelerometerSensor::getZAcceleration(){
    return lis.getAccelerationZ();
}

float AccelerometerSensor::getTotalAcceleration(float accelerationX, float accelerationY, float accelerationZ){
    return sqrt((accelerationX * accelerationX) + (accelerationY * accelerationY) + (accelerationZ * accelerationZ));
}

float AccelerometerSensor::getSensorValue() {

    /* 
    The Wio has a base acceleration around -1 in total depending on the rotation of the wio which has to be accounted for.
    We account for this by calibrating before the car starts moving and removing it everytime we receive the speed.
    */
    accelerationX = getXAcceleration() - calibrationX;
    accelerationY = getYAcceleration() - calibrationY;
    accelerationZ = getZAcceleration() - calibrationZ;

    /* 
    The values might drift a bit, since we know the arduino will not accelerate with an acceleration of only 0.07
    we can safely remove anything less than that.
    */
    accelerationX = (abs(accelerationX) < 0.07) ? 0 : accelerationX;
    accelerationY = (abs(accelerationY) < 0.07) ? 0 : accelerationY;
    accelerationZ = (abs(accelerationZ) < 0.07) ? 0 : accelerationZ;

    totalAcceleration = getTotalAcceleration(accelerationX,accelerationY, accelerationZ);

    // Find out if the acceleration is negative (driving backwards)
    if ((accelerationX * accelerationY * accelerationZ) < 0 ){
        totalAcceleration = totalAcceleration * -1;
    }

    arduinoSpeed = updateSpeed();

    return arduinoSpeed;
}

float AccelerometerSensor::updateSpeed(){
    currentAccelerationTime = millis();
    currentSpeedTime = millis();

    // Assuming constant acceleration in the timeframe.
    arduinoSpeed = previousSpeed + totalAcceleration * (currentAccelerationTime - previousAccelerationTime) / msRatio;
    

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

float AccelerometerSensor::getTravelledDistance(){

    // Make sure everything is fully updated.
    getSensorValue();

    return distanceTravelled;
    
}

AccelerometerSensor::~AccelerometerSensor() {}
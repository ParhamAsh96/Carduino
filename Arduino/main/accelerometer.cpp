#include "arduino.h"
#include "LIS3DHTR.h"
#include "PubSubClient.h"
#include "ArduinoSensor.h"
#include "accelerometer.h"
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

    previousTime = millis();

}

void AccelerometerSensor::publishMQTT(float sensorValue) {
    char returnMessage[5];
    dtostrf(sensorValue, 0, 2, returnMessage);

    client.publish(topic, returnMessage);
}

float AccelerometerSensor::getSensorValue() {


    xValue = lis.getAccelerationX();
    yValue = lis.getAccelerationY();
    /* 
    zValue has some noise and shows 1 less than the actual acceleration. (-1 when standing still) 
    This depends on how the Arduino is positioned and has to be accounted for when placing the arduino in the chassis.
    */
    zValue = lis.getAccelerationZ() + 1;

    
    totalAcceleration = sqrt((xValue * xValue) + (yValue * yValue) + (zValue * zValue));

    currentTime = millis();

    // Assuming constant acceleration in the timeframe.
    arduinoSpeed = previousSpeed + totalAcceleration * (currentTime - previousTime) / msRatio;
    previousTime = currentTime;
    
    return arduinoSpeed;
}

AccelerometerSensor::~AccelerometerSensor() {}
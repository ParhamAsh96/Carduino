#include "LIS3DHTR.h"
#include "AccelerometerSensor.h"
#include "BrakeLight.h"

brakeLight = D1; 

float previousSpeedTime = 0;
float arduinoSpeed = 0;

float BrakeLight::getPreviousSpeedTime() {
    return previousSpeedTime;
}

float BrakeLight::getArduinoSpeed() {
    return arduinoSpeed;
}

void updateFromSensor(const AccelerometerSensor& s) {
  arduinoSpeed      = s.getSensorValue();
  previousSpeedTime = s.getPreviousSpeedTime();
}
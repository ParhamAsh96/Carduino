#include <ChainableLED.h>
#include "AccelerometerSensor.h"
#include "BrakeLight.h"

BrakeLight::BrakeLight(int pin)
  : brakeLight(pin), previousSpeed(0), currentSpeed(0) {
    pinMode(brakeLight, OUTPUT);
  }
  
const int brakeLight = D1; 

void BrakeLight::TurnOnBrakeLight(float currentSpeed, float previousSpeed)
{
  if (currentSpeed < previousSpeed) {
    digitalWrite(brakeLight, HIGH);

  } else {
    digitalWrite(brakeLight, LOW);
  }
}

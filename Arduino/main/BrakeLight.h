#include <ChainableLED.h>
#include "AccelerometerSensor.h"

class BrakeLight {
public:

  BrakeLight(int pin);

  void TurnOnBrakeLight(float currentSpeed, float previousSpeed);

private:

  const int brakeLight;

  float previousSpeed;
  
  float currentSpeed;
};

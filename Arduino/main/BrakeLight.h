#include "AccelerometerSensor.h"

class BrakeLight
{

  private:

    const int brakeLight;

    float previousSpeed;

    float currentSpeed;


  public:

    float previousSpeed;

    float currentSpeed = accelerometer.getSpeed();
    
    int TurnOnBrakeLight(float currentSpeed, float previousSpeed);

};
#include "AccelerometerSensor.h"

class BrakeLight
{

  private:

    const int brakeLight;

    float previousSpeedTime;

    float arduinoSpeed;


  public:
  
    float previousSpeed;

    float currentSpeed = accelerometer.getSpeed();
    
    int TurnOnBrakeLight(float arduinoSpeed, float previousSpeedTime);

};
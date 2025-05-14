#include "AccelerometerSensor.h"

class BrakeLight
{

  private:

    const int brakeLight;

    float previousSpeedTime;

    float arduinoSpeed;

  public:

    void setup();

    float getPreviousSpeedTime();
    
    float getArduinoSpeed();

    float CalculateBrakeSpeed(float newCurrentSpeed, float arduinoSpeed);
    
    int TurnOnBrakeLight(float arduinoSpeed, float newCurrentSpeed);

};
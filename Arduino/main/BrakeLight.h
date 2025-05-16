#ifndef BRAKELIGHTS_H
#define BRAKELIGHTS_H

#include <Arduino.h>

class BrakeLight {
  public:
      BrakeLight(int pin);
      void setup();
      void brakeLightOnRed();
      void brakeLightOnYellow();
      void brakeLightOff();

  private:
      const int brakeLight;
      bool lightTurnOn;
      bool lightTurnOff;
};

#endif
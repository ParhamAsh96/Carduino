#ifndef BRAKELIGHT_H
#define BRAKELIGHT_H

#include <Arduino.h>
#include <ChainableLED.h>

class BrakeLight {

  public:
      BrakeLight();
      void setup();
      void init();
      void setColorRGB();
      void brakeLightOnRed();
      void brakeLightOnWhite();
      void brakeLightOff();
      void lightReceiver(const String& message);

  private:
        const int LED_NUM;
        const int CLK_PIN;
        const int DAT_PIN;
        bool enabled;
        ChainableLED brakeLight;

};

extern BrakeLight brakeLight;

#endif
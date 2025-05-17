#include <ChainableLED.h>
#include "PubSubClient.h"
#include "CarController.h"
#include "BrakeLight.h"

BrakeLight::BrakeLight()
    : LED_NUM(1), CLK_PIN(A0), DAT_PIN(A1), brakeLight(CLK_PIN, DAT_PIN, LED_NUM)
{

}

void BrakeLight::setup() {
  const int LED_NUM = 1;
  const int CLK_PIN = A0;
  const int DAT_PIN = A1;

  brakeLight.init();
}

void BrakeLight::brakeLightOnRed() {
  brakeLight.setColorRGB(0, 255, 0, 0);
  bool lightTurnOn = true;
}

void BrakeLight::brakeLightOnYellow() {
  brakeLight.setColorRGB(0, 255, 255, 0);
  bool lightTurnOn = true;
}

void BrakeLight::brakeLightOff() {
  brakeLight.setColorRGB(0, 0, 0, 0);
  bool lightTurnOff = false;
}
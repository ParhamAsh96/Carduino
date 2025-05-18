#include <ChainableLED.h>
#include "PubSubClient.h"
#include "CarController.h"
#include "BrakeLight.h"

BrakeLight::BrakeLight()
    : LED_NUM(2), CLK_PIN(A0), DAT_PIN(A1), brakeLight(CLK_PIN, DAT_PIN, LED_NUM), enabled(true)
{

}

void BrakeLight::setup() {
  Serial.println("[BrakeLight] setup()");
  brakeLight.init();
  brakeLightOnRed();
}

void BrakeLight::brakeLightOnRed() {
  if (!enabled) {
    return; 
    } else {
    brakeLight.init();
    brakeLight.setColorRGB(0, 255, 0, 0);
    brakeLight.setColorRGB(1, 255, 0, 0);
    Serial.println("Red LEDs On");
  }
}

void BrakeLight::brakeLightOnWhite() {
  if (!enabled) {
    return; 
    } else {
    brakeLight.init();
    brakeLight.setColorRGB(0, 255, 255, 255);
    brakeLight.setColorRGB(1, 255, 255, 255);
    Serial.println("White LEDs On");
  }
}

void BrakeLight::brakeLightOff() {
  brakeLight.init();
  brakeLight.setColorRGB(0, 0, 0, 0);
  brakeLight.setColorRGB(1, 0, 0, 0);
  Serial.println("LEDs Off");
}

void BrakeLight::lightReceiver(const String& message) 
{
  if (message == "lightOn") {
      enabled = true;
  } 

  if (message == "lightOff") {
      enabled = false;
      brakeLightOff();
  } 
}

#include <ChainableLED.h>
#include "PubSubClient.h"
#include "CarController.h"
#include "BrakeLight.h"

BrakeLight::BrakeLight()
    : LED_NUM(1), CLK_PIN(A0), DAT_PIN(A1), brakeLight(CLK_PIN, DAT_PIN, LED_NUM), enabled(true)
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
    Serial.println("Red called");
  }
}

void BrakeLight::brakeLightOnYellow() {
  if (!enabled) {
    return; 
    } else {
    brakeLight.init();
    brakeLight.setColorRGB(0, 255, 255, 0);
    Serial.println("Yellow called");
  }
}

void BrakeLight::brakeLightOff() {
  brakeLight.init();
  brakeLight.setColorRGB(0, 0, 0, 0);
  Serial.println("Turn off called");
}

void BrakeLight::lightReceiver(const String& message) 
{
  if (message == "turnOn") {
      enabled = true;
  } 

  if (message == "turnOff") {
      enabled = false;
      brakeLightOff();
  } 
}

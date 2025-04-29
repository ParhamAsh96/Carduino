#include "arduino.h"
#include "PubSubClient.h"
#include "ArduinoSensor.h"
#include "TemperatureSensor.h"
#include <sstream>

TemperatureSensor::TemperatureSensor(PubSubClient& client, const char* topic)
    : client(client), topic(topic) {}

void TemperatureSensor::setup() {
    // Startup values
    betaCoefficient = 4275;               
    baseResistance = 100000;            
    pinTempSensor = A0;

    pinMode(pinTempSensor, INPUT);
}

void TemperatureSensor::publishMQTT(float sensorValue) {
    char returnMessage[5];
    dtostrf(sensorValue, 0, 2, returnMessage);

    client.publish(topic, returnMessage);
}

float TemperatureSensor::getSensorValue() {
    int sensorValue = analogRead(pinTempSensor);
    float temperatureResistance = 1023.0/sensorValue-1.0;
    temperatureResistance = baseResistance*temperatureResistance;
    float temperature = 1.0/(log(temperatureResistance/baseResistance)/betaCoefficient+1/298.15)-273.15; // convert to temperature via datasheet

    
    return temperature;
}

TemperatureSensor::~TemperatureSensor() {}


#ifndef ARDUINO_SENSOR_H
#define ARDUINO_SENSOR_H

#include <PubSubClient.h>

class ArduinoSensor {
public:
    virtual void publishMQTT(float sensorValue) = 0;
    virtual float getSensorValue() = 0;
    virtual void setup() = 0;
    virtual ~ArduinoSensor() = default;
};

#endif
#include "linefinder.h"

// Constructor
LineFinder::LineFinder(PubSubClient& client, const char* topic, int sensorPin)
    : _client(client), _topic(topic), _sensorPin(sensorPin), _autoBrakeTriggered(false), _lastLineLostTime(0) {}

//initialize the sensor pin
void LineFinder::setup() {
    pinMode(_sensorPin, INPUT); 
}

//reads the sensors value
int LineFinder::getSensorValue() {
    return digitalRead(_sensorPin);
}

//checks if the line is detected and triggers the auto-brake
void LineFinder::checkAndTriggerAutoBrake() {
    int sensorValue = getSensorValue();
     unsigned long currentMillis = millis();  // Get the current time in milliseconds
    //if no line
     if (sensorValue == HIGH) {  // If the sensor detects no line
        if (!_autoBrakeTriggered) {
            // Check if the line has been lost for 5 seconds or more
            if (currentMillis - _lastLineLostTime >= 5000) {  
                _autoBrakeTriggered = true;  // Trigger the auto-brake
                // Code to engage the auto-brake goes here,but we dont have it yet
                Serial.println("Auto-brake triggered: No line detected for 5 seconds.");
            }
        }
    } else {
        // Reset the time tracker if the line is found
        _lastLineLostTime = currentMillis;
        if (_autoBrakeTriggered) {
            _autoBrakeTriggered = false;  // Disable the auto-brake once the line is found again
            // Code to disengage the auto-brake goes here
            Serial.println("Auto-brake disengaged: Line detected.");
        }
    }
}


void LineFinder::publishMQTT(float sensorValue) {
     sensorValue = getSensorValue();  
    char returnMessage[5];
    
    // Convert the sensor value (HIGH or LOW) to a string
    dtostrf(sensorValue, 0, 0, returnMessage);

    // Publish the sensor data to the specified MQTT topic
    _client.publish(_topic, returnMessage);
}



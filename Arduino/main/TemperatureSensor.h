#include "ArduinoSensor.h"
#include "PubSubClient.h"

class TemperatureSensor : public ArduinoSensor{
    public: 
    
        // Class functions
    
        TemperatureSensor(PubSubClient& client, const char* topic);
    
        void setup();
    
        void publishMQTT(float sensorValue) override;
        
        
        float getSensorValue() override;
    
        ~TemperatureSensor();

private:

    // For sensor values and and converting from sensor values to temperature
    
    float temperature;
    int betaCoefficient;              
    int baseResistance;       
    int pinTempSensor;


    // Pointer to PubSubClient from main and topic
    PubSubClient& client;
    const char *topic;

    };
    
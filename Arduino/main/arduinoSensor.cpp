class ArduinoSensor{
    public:

        virtual void publishMQTT(float sensorValue) = 0;
        virtual float* getSensorValue() = 0;
        
};


class ArduinoSensor{
    public:

        virtual void publishMQTT() = 0;
        virtual float* getSensorValue() = 0;
        
};


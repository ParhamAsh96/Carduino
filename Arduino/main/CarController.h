#ifndef CAR_CONTROLLER_H
#define CAR_CONTROLLER_H

#include <Arduino.h>
#include "BrakeLight.h"


class CarController {
public:
    CarController(BrakeLight& bl);  // Constructor
    void setup();                                   // Set pinMode for motors
    void arrowUp();                                 
    void arrowDown();                               
    void arrowLeft();                               
    void arrowRight();                              
    void arrowUpStop();                                 
    void arrowDownStop();                               
    void arrowLeftStop();                               
    void arrowRightStop();                              
    void wheelsReceiver(String message);  // Message handler
    bool getDrivingStatus();

private:
    int leftForward;
    int leftBackward;
    int rightForward;
    int rightBackward;
    bool goingForward;
    bool goingBackward;
    BrakeLight& brakeLight;
};

#endif

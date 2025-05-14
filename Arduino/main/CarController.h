#ifndef CAR_CONTROLLER_H
#define CAR_CONTROLLER_H


class CarController {
public:
    CarController();  // Constructor
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

private:
    int leftForward;
    int leftBackward;
    int rightForward;
    int rightBackward;
    bool goingForward;
    bool goingBackward;
};

#include "CarController.h"
#include "PubSubClient.h"
#include "BrakeLight.h"


CarController::CarController(BrakeLight& bl)
    : brakeLight(bl)
{

}


void CarController::setup() {
    leftForward = D6;
    leftBackward = D5;
    rightForward = D7;
    rightBackward = D8;

    goingForward = false;
    goingBackward = false;
    goingRight = false;
    goingLeft = false;

    pinMode(leftForward, OUTPUT);
    pinMode(leftBackward, OUTPUT);
    pinMode(rightForward, OUTPUT);
    pinMode(rightBackward, OUTPUT);
}

void CarController::arrowUp() {
    if (goingLeft){
        digitalWrite(rightForward, HIGH);
    }
    else if (goingRight){
        digitalWrite(leftForward, HIGH);
    }
    else{
        digitalWrite(leftForward, HIGH);
        digitalWrite(rightForward, HIGH);
    }
    goingForward = true;
    brakeLight.brakeLightOff();
}


void CarController::arrowDown() {
    if (goingLeft){
        digitalWrite(rightBackward, HIGH);
    }
    else if (goingRight){
        digitalWrite(leftBackward, HIGH);
    }
    else{
        digitalWrite(leftBackward, HIGH);
        digitalWrite(rightBackward, HIGH);
    }
    goingBackward = true;
    brakeLight.brakeLightOnWhite();
}

void CarController::arrowLeft() {
    if (goingForward)
    {
        digitalWrite(leftForward, LOW);
        brakeLight.brakeLightOff();
    }
    else if (goingBackward)
    {
        digitalWrite(leftBackward, LOW);
        brakeLight.brakeLightOnWhite();
    }
    goingLeft = true;
    
}

void CarController::arrowRight() {
    if (goingForward)
    {
        digitalWrite(rightForward, LOW);
        brakeLight.brakeLightOff();
    }
    else if (goingBackward)
    {
        digitalWrite(rightBackward, LOW);
        brakeLight.brakeLightOnWhite();
    }
    goingRight = true;
    
}

void CarController::arrowUpStop() {
    digitalWrite(leftForward, LOW);
    digitalWrite(rightForward, LOW);
    goingForward = false;
    brakeLight.brakeLightOnRed();
}

void CarController::arrowDownStop() {
    digitalWrite(leftBackward, LOW);
    digitalWrite(rightBackward, LOW);
    goingBackward = false;
    brakeLight.brakeLightOnRed();
}

void CarController::arrowLeftStop() {
    if (goingForward)
    {
        digitalWrite(leftForward, HIGH);
        brakeLight.brakeLightOff();
    }
    else if (goingBackward)
    {
        digitalWrite(leftBackward, HIGH);
        brakeLight.brakeLightOnWhite();
    }
    goingLeft = false;
    
}

void CarController::arrowRightStop() {
    if (goingForward)
    {
        digitalWrite(rightForward, HIGH);
        brakeLight.brakeLightOff();
    }
    else if (goingBackward)
    {
        digitalWrite(rightBackward, HIGH);
        brakeLight.brakeLightOnWhite();
    }
    goingRight = false;
}

void CarController::wheelsReceiver(String message) 
{
        if (message == "arrowUp") {
            arrowUp();
        } if (message == "arrowDown") {
            arrowDown();
        } if (message == "arrowLeft") {
            arrowLeft();
        } if (message == "arrowRight") {
            arrowRight();
        } if (message == "arrowUpStop") {
            arrowUpStop();}
         if (message == "arrowDownStop") {
            arrowDownStop();
        } if (message == "arrowLeftStop") {
            arrowLeftStop();
        } if (message == "arrowRightStop") {
            arrowRightStop();
        }
    
}
bool CarController::getDrivingStatus(){
    return (goingForward || goingBackward);
}

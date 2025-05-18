#include "CarController.h"
#include "PubSubClient.h"
#include "BrakeLight.h"


CarController::CarController(BrakeLight& bl)
    : brakeLight(bl)
{

}


void CarController::setup() {
    leftForward = D1;
    leftBackward = D4;
    rightForward = D2;
    rightBackward = D3;

    pinMode(leftForward, OUTPUT);
    pinMode(leftBackward, OUTPUT);
    pinMode(rightForward, OUTPUT);
    pinMode(rightBackward, OUTPUT);
}

void CarController::arrowUp() {
    digitalWrite(leftForward, HIGH);
    digitalWrite(rightForward, HIGH);
    goingForward = true;
    brakeLight.brakeLightOff();
}


void CarController::arrowDown() {
    digitalWrite(leftBackward, HIGH);
    digitalWrite(rightBackward, HIGH);
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

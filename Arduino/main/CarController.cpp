#include "CarController.h"
#include "PubSubClient.h"



CarController::CarController()
{

}


void CarController::setup() {
    leftForward = D0;
    leftBackward = D1;
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
    goingBackward = false;
}


void CarController::arrowDown() {
    digitalWrite(leftBackward, HIGH);
    digitalWrite(rightBackward, HIGH);
    goingForward = false;
    goingBackward = true;

}

void CarController::arrowLeft() {
    digitalWrite(leftForward, LOW);
    digitalWrite(leftBackward, LOW);
}

void CarController::arrowRight() {
    digitalWrite(rightForward, LOW);
    digitalWrite(rightBackward, LOW);
}

void CarController::arrowUpStop() {
    digitalWrite(leftForward, LOW);
    digitalWrite(rightForward, LOW);
}

void CarController::arrowDownStop() {
    digitalWrite(leftBackward, LOW);
    digitalWrite(rightBackward, LOW);
}

void CarController::arrowLeftStop() {
    if (goingForward)
    {
        digitalWrite(leftForward, HIGH);
    }
    else if (goingBackward)
    {
        digitalWrite(leftBackward, HIGH);
    }
    
}

void CarController::arrowRightStop() {
    if (goingForward)
    {
        digitalWrite(rightForward, HIGH);
    }
    else if (goingBackward)
    {
        digitalWrite(rightBackward, HIGH);
    }
}

void CarController::wheelsReceiver(String message) 
{
        if (message == "arrowUp") {
            arrowUp();
        } else if (message == "arrowDown") {
            arrowDown();
        } else if (message == "arrowLeft") {
            arrowLeft();
        } else if (message == "arrowRight") {
            arrowRight();
        } else if (message == "arrowUpStop") {
            arrowUpStop();}
        else if (message == "arrowDownStop") {
            arrowDownStop();
        } else if (message == "arrowLeftStop") {
            arrowLeftStop();
        } else if (message == "arrowRightStop") {
            arrowRightStop();
        }
    
}

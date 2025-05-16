#include "CarController.h"
#include "PubSubClient.h"



CarController::CarController()
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
}


void CarController::arrowDown() {
    digitalWrite(leftBackward, HIGH);
    digitalWrite(rightBackward, HIGH);
    goingBackward = true;

}

void CarController::arrowLeft() {
    if (goingForward)
    {
        digitalWrite(leftForward, LOW);
    }
    else if (goingBackward)
    {
        digitalWrite(leftBackward, LOW);
    }

}

void CarController::arrowRight() {
    if (goingForward)
    {
        digitalWrite(rightForward, LOW);
    }
    else if (goingBackward)
    {
        digitalWrite(rightBackward, LOW);
    }
    
}

void CarController::arrowUpStop() {
    digitalWrite(leftForward, LOW);
    digitalWrite(rightForward, LOW);
    goingForward = false;
}

void CarController::arrowDownStop() {
    digitalWrite(leftBackward, LOW);
    digitalWrite(rightBackward, LOW);
    goingBackward = false;
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

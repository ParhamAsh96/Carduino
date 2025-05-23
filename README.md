# Carduino

## Purpose and Benefits

## Hardware and Software Architecture

## Setup Instructions

To set up the carduino, you have to first plug in all the cables for the sensors as follows;

The LEDs need to be plugged into A0 and A1.

The temperature sensor needs to be plugged into A2.

The motors need to be set up as follows: 

The left motor in the back needs to be hooked up to D5

The left motor in the front needs to be hooked up to D6

The right motor in the front needs to be hooked up to D7

The right motor in the back needs to be hooked up to D8

Afterwards you need to update the internet credentials in the arduino file main.ino on line 16 and 17. If you are using a public wifi and it does not work, try to change your wifi to a private one, or change to cellular.

Then you need to download the dependencies for the arduino from the shellscript named setup-build-env.sh.
Now you are ready to upload the code to the Wio Terminal! Simply open up the Arduino IDE, plug in the Wio Terminal and click on upload.

Now that the Wio Terminal is set up you should set up the web page.
This is a short process compared to the hardware components. All you need to do is to open up cmd, navigate to the Web_App folder, and write:

`npm install`

`npm run dev`

`o`

and the webpage should be opened up!

### Problems

Some problems might occur with the MQTT connection. Keep in mind, this is not a hardware issue. This is a broker issue, so to resolve this issue, you should change the broker in Arduino/main/main.ino on line 23 and in Web_App/src/client.js you need to change the broker on line 40.
You could use the following public brokers:

broker.hivemq.com

test.mosquttio.org

However, there are always certain risks with using public brokers, if you wish to use a secure private broker, please open up a local broker on your own computer or get a private online broker.

## Contributions

This project has had 5 contributors. Their names are and contributions are:

#### Makan Ajdadi Salekdeh

Set up the motors and movement of the car.

#### Ali Parham Ashrafzadeh

Set up the lights and power preservation of the car.

#### Dorin Calmis

Set up the diagnostics history of the car and the music buzzer

#### Sivert Bronebakk

Set up the diagnostics sensors for the car

#### Mobin Salehi

Set up music buzzer and MQTT component in the Vue project


## Demo Video

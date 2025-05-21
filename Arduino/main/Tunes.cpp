#include "Tunes.h"

Tunes::Tunes(PubSubClient* client, String* topic) 
    : client(client), recTopic(topic) {
}

void Tunes::setup() {
    pinMode(BUZZER_PIN, OUTPUT);
}

bool Tunes::checkWheels() {
    if(buzzerRuns) {
        buzzerRuns = false;
        return true;
    }
    return false;
}

void Tunes::tuneReceiver(const String& message) {
    buzzerRuns = true;
    if (message == "honk") honk(0);
    if (message == "tune") honk(1);
    if (message == "anthem") honk(2);
    buzzerRuns = false;
}

void Tunes::honk(int option) {
    switch(option) {
        case 0: // honk
            playTone(1519, 1000);
            break;
        case 1: // tune
            readMusicSheet(notes_tune, beats_tune, 15);
            break;
        case 2: // anthem
            readMusicSheet(notes_anthem, beats_anthem, 19);
            break;
        default: 
            Serial.println("tune not found");
    }
}

void Tunes::readMusicSheet(const char notes[], const int beats[], int length) {
    for(int i = 0; i < length; i++) {
        if(notes[i] == ' ') {
            delay(beats[i] * tempo);
            if (checkMqtt()) return;
        } else {
            playNote(notes[i], beats[i] * tempo);
            if (checkMqtt()) return;
        }
        delay(tempo / 2);
    }
}

void Tunes::playNote(char note, int duration) {
    const char names[] = {'c','d','e','f','g','a','b','C'};
    const int tones[] = {1915,1700,1519,1432,1275,1136,1014,956};

    for(int i = 0; i < 8; i++) {
        if(names[i] == note) {
            playTone(tones[i], duration);
            if(checkMqtt()) return;
        }
    }
}

void Tunes::playTone(int tone, int duration) {
    for(long i = 0; i < duration * 1000L; i += tone * 2) {
        digitalWrite(BUZZER_PIN, HIGH);
        delayMicroseconds(tone);
        digitalWrite(BUZZER_PIN, LOW);
        delayMicroseconds(tone);
    }
}

bool Tunes::checkMqtt() {
    client->loop();
    return (*recTopic == "carduino/movement");
}
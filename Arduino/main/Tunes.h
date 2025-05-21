#ifndef TUNES_H
#define TUNES_H

#include <Arduino.h>
#include <PubSubClient.h>
#include <WiFiClient.h>

#define BUZZER_PIN WIO_BUZZER

class Tunes {
private:
    PubSubClient* client;
    String* recTopic;
    bool buzzerRuns = false;
    const int tempo = 200;
    
    char notes_tune[16] = "ccggaagffeeddc ";
    int beats_tune[15] = { 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4 };
    char notes_anthem[16] = "ggecg edc ggecg";
    int beats_anthem[19] = {2,2,2,1,1,4, 2,2,4, 2,2,2,1,1,4, 2,2,4, 4};

    void honk(int option);
    void playTone(int tone, int duration);
    void playNote(char note, int duration);
    void readMusicSheet(const char notes[], const int beats[], int length);
    bool checkMqtt();

public:
    Tunes(PubSubClient* client, String* recTopic);
    void setup();
    void tuneReceiver(const String& message);
    bool checkWheels();
};

#endif
#ifndef __PONG_PLAYER_CPP
#define __PONG_PLAYER_CPP

#include "Sound.h"

void Sound::begin() {
  pinMode(_buzzerPin, OUTPUT);
}

void Sound::play(int frequency, int duration) {
  tone(_buzzerPin, frequency);
  // FIXME!!! change to non-blocking
  delay(duration);
  noTone(_buzzerPin);
}

void Sound::playStartGame() {
  play(1000, 200);
}


void Sound::playBounce() {
  play(500, 25);
}


void Sound::playSmash() {
  play(700, 50);
}


void Sound::playSuperSmash() {
  play(900, 50);
}


void Sound::playScore() {
  play(200, 500);
}


void Sound::playVictory() {
  play(800, 250);
  play(800, 250);
  play(1000, 250);
  play(1200, 500);
  play(1000, 250);
  play(1200, 1000);
}


#endif

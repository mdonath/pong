#ifndef __PONG_SOUND_H
#define __PONG_SOUND_H

#include <Arduino.h>

class Sound {
  public:
    Sound(byte buzzerPin) :
      _buzzerPin(buzzerPin)
    {}

    void begin();
    void playStartGame();
    void playBounce();
    void playSmash();
    void playSuperSmash();
    void playScore();
    void playVictory();

  private:
    byte _buzzerPin;

    void play(int frequency, int duration);
};

#endif

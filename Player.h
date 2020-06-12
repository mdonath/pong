#ifndef __PONG_PLAYER_H
#define __PONG_PLAYER_H

#include <Arduino.h>
#include <FastLED.h>
#include "Zone.h"
#include "Ball.h"

class Zone;
class Ball;

/**
   One of the players of the game.
*/
class Player {

  public:

    Player(byte pin, Color color):
      _buttonPin(pin),
      color(color)
    { }

    void begin();
    void setZone(Zone *zone);

    bool isLeftPlayer();
    bool isRightPlayer();
    int getHomePosition();

    void forgetPosition();
    void rememberPosition(int position);
    void reset();
    void addPoint();
    int getScore();
    bool isButtonPressed();
    void indicateStart(int brightness);

    bool hasButtonPressedInEndZone(Ball *ball);
    void disable();
    void enable();
    bool isSuperBoost(Ball *ball);
    bool isNormalBoost(Ball *ball);
    bool isPastEndZone(Ball *ball);

    void rememberPressed();
    bool hasAlreadyPressedButton();
    void forgetPressed();

    bool isPressingButton();
    boolean buttonBounce(byte bounceTime);

    void waitForButtonPress();
    void waitForButtonRelease();

    Color color;

    bool alreadyPressedButton = false;

  private:
    byte _buttonPin;
    int _score;
    Zone *_zone;

    int readButton();
    bool isButtonReleased();

};
#endif

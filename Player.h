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
    {
    }

    void begin(Zone *zone);

    bool isLeftPlayer() {
      return _zone->getHomePosition() < 25;
    };
    bool isRightPlayer() {
      return !isLeftPlayer();
    };
    int getHomePosition();

    void forgetPosition();
    void rememberPosition(int position);
    void reset();
    void addPoint();
    int getScore() {
      return _score;
    }
    bool isButtonPressed();

    bool hasButtonPressedInEndZone(Ball *ball);
    bool isSuperBoost(Ball *ball);
    bool isNormalBoost(Ball *ball);
    bool isPastEndZone(Ball *ball);

    void setSetupMode();
    void setGameMode();
    void drawZone(CRGB *leds, int brightness);

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

    int readButton();
    bool isButtonReleased();

    Zone *_zone;

    byte _buttonPin;

    int _score;

};
#endif

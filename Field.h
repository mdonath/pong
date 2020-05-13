#ifndef __PONG_FIELD_H
#define __PONG_FIELD_H

#include <FastLED.h>
#include "Game.h"
#include "Player.h"
#include "Ball.h"
#include "Colors.h"
#include "Zone.h"

class Game;
class Player;

/**
   The 1 dimensional field on which the game is played.
*/
class Field {
  public:

    template<uint8_t STRIP_DATA_PIN> void begin(int numberOfLeds, Game *game) {
      _game = game;
      _numberOfLeds = numberOfLeds;
      leds = new CRGB[_numberOfLeds];
      FastLED.addLeds<NEOPIXEL, STRIP_DATA_PIN>(leds, _numberOfLeds);
    }

    void clear();
    void nextBrightness();

    void draw(bool show = true);
    void drawDimmed(bool show = true);

    void drawMovingBall(Ball *ball);
    void drawBallAtPlayerAndWait(Ball *ball, Player *player);

    void rememberButtonPress(Ball *ball, Player *player);
    void forgetButtonPress();

    void blinkNewScore(Player *player);
    void showSetupMode();
    void showGameMode();
    void showRainbow(boolean won);

    int size();

  private:

    Game *_game;
    int _maxBrightness = 50;

    int _numberOfLeds;
    CRGB *leds;


    int previousButtonPos = -1;                 // position of last button-press
    unsigned long previousButtonMillis;         // time of last button-press
    Color previousButtonColor;                  // color of field for last button-press


    void draw(byte scoreBrightness, bool show);
    void drawBall(Ball *ball, Color color, byte saturation = 255);
    void drawEndZone();
    void drawScore(int brightness);
    void drawLastHit();

};


#endif

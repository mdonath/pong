#ifndef __PONG_FIELD_CPP
#define __PONG_FIELD_CPP

#include "Field.h"
#include "Game.h"
#include <colorutils.h>


void Field::clear() {
  FastLED.clear();
}

void Field::nextBrightness() {
  _maxBrightness += 50;
  if (_maxBrightness > 255) {
    _maxBrightness = 55;
  }
  clear();
  drawEndZone();
  FastLED.show();
}

void Field::drawDimmed(const bool show) {
  draw(_maxBrightness / 2, show);
}

void Field::draw(const bool show) {
  draw(_maxBrightness, show);
}

void Field::draw(const byte scoreBrightness, const bool show) {
  clear();
  drawEndZone();
  drawScore(scoreBrightness);
  drawLastHit();
  if (show) {
    FastLED.show();
  }
}

void Field::drawBall(Ball *ball, const Color color, const byte saturation) {
  ball->draw(leds, color, saturation, _maxBrightness);
  FastLED.show();
}

void Field::drawMovingBall(Ball *ball) {
  ball->drawMoving(leds, _maxBrightness);
  FastLED.show();
}
  
void Field::drawBallAtPlayerAndWait(Ball *ball, Player *player) {
  ball->startAt(player);

  drawBall(ball, player->color);
  player->waitForButtonPress();
  drawBall(ball, Color::ENDZONE_GAME);
}


void Field::rememberButtonPress(Ball *ball, Player *player) {
  previousButtonPos = ball->position();
  previousButtonColor = player->color;
  previousButtonMillis = millis(); // store time when button was pressed
  player->rememberPressed();
}


void Field::forgetButtonPress() {
  previousButtonPos = -1;
}

void Field::showSetupMode() {
  _game->getPlayer(1)->setSetupMode();
  _game->getPlayer(2)->setSetupMode();
};

void Field::showGameMode() {
  _game->getPlayer(1)->setGameMode();
  _game->getPlayer(2)->setGameMode();
};

int Field::size() {
  return _numberOfLeds;
}


void Field::blinkNewScore(Player* const player) {
  int pos = _numberOfLeds / 2;
  if (player->isLeftPlayer()) {
    pos -= player->getScore();
  } else {
    pos += player->getScore() - 1;
  }
  Color color = player->color;

  draw(false);

  for (int i = 1; i <= 4; i++) {
    leds[pos] = CHSV(color, 255, (i % 2) * _maxBrightness);  // blink LED 2 times (1-0-1-0)
    FastLED.show();
    delay(300);
  }
}


void Field::drawEndZone() {
  _game->getPlayer(1)->drawZone(leds, _maxBrightness);
  _game->getPlayer(2)->drawZone(leds, _maxBrightness);
}


/**
   Draws the scores of both players in the middle of the field.
*/
void Field::drawScore(const int brightness) {
  int halfNumberOfLeds = _numberOfLeds / 2;

  for (int i = 0; i < _game->getPlayer(1)->getScore(); i++) {
    leds[halfNumberOfLeds - 1 - i] = CHSV(_game->getPlayer(1)->color, 255, brightness);
  }

  for (int i = 0; i < _game->getPlayer(2)->getScore(); i++) {
    leds[halfNumberOfLeds + i] = CHSV(_game->getPlayer(2)->color, 255, brightness);
  }
}


/**
    Draws mark of position of last button-press.
*/
void Field::drawLastHit() {
  if (previousButtonPos != -1 && previousButtonMillis + 500 > millis()) {
    leds[previousButtonPos] = CHSV(previousButtonColor, 255, 0);
  }
}


void Field::showRainbow(const boolean won) {
  clear();
  for (int k = 0; k < 750; k++) {  // several rounds rainbow
    fill_rainbow(&(leds[won ? 0 : 30]), 30, millis() / 10);
    fadeToBlackBy(leds, 60, 255 - (_maxBrightness / 4));
    FastLED.show();
    delay(7);
  }
}


#endif

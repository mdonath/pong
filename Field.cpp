#ifndef __PONG_FIELD_CPP
#define __PONG_FIELD_CPP

#include "Field.h"
#include "Game.h"
#include <colorutils.h>

Field::Field(int numberOfLeds, int zoneLength) :
  _numberOfLeds(numberOfLeds)
{
  _zone1 = new Zone(this, 0, zoneLength);
  _zone2 = new Zone(this, _numberOfLeds - 1, -zoneLength);

  _score = new ScoreBoard(this, _numberOfLeds);
}

void Field::clear() {
  FastLED.clear();
}

void Field::setLed(int position, CHSV color, bool show) {
  _leds[position] = color;
  if (show) {
    FastLED.show();
  }
}


void Field::setupNextBrightness() {
  _maxBrightness += 50;
  if (_maxBrightness > 255) {
    _maxBrightness = 55;
  }
  clear();
  drawEndZone();
  FastLED.show();
}

void Field::assignToZone1(Player *player) {
  player->setZone(_zone1);
}

void Field::assignToZone2(Player *player) {
  player->setZone(_zone2);
}

bool Field::isPastEndZones(Ball *ball) {
  int pos = ball->position();
  return _zone1->isPastEndZone(pos) || _zone2->isPastEndZone(pos);
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
  ball->draw(color, saturation, _maxBrightness);
  FastLED.show();
}

void Field::drawMovingBall(Ball *ball) {
  ball->drawMoving(_maxBrightness);
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
  _zone1->setSetupMode();
  _zone2->setSetupMode();
};

void Field::showGameMode() {
  _zone1->setGameMode();
  _zone2->setGameMode();
};

int Field::size() {
  return _numberOfLeds;
}

void Field::blinkNewScore(Player *player) {
  _score->blinkNewScore(player, _maxBrightness);
}


void Field::drawEndZone() {
  _zone1->draw(_maxBrightness);
  _zone2->draw(_maxBrightness);
}


/**
   Draws the scores of both players in the middle of the field.
*/
void Field::drawScore(const int brightness) {
  _score->draw(_zone1->getPlayer(), _zone2->getPlayer(), brightness);
}


/**
    Draws mark of position of last button-press.
*/
void Field::drawLastHit() {
  if (previousButtonPos != -1 && previousButtonMillis + 500 > millis()) {
    _leds[previousButtonPos] = CHSV(previousButtonColor, 255, 0);
  }
}


void Field::showRainbow(const boolean won) {
  clear();
  for (int k = 0; k < 750; k++) {  // several rounds rainbow
    fill_rainbow(&(_leds[won ? 0 : 30]), 30, millis() / 10);
    fadeToBlackBy(_leds, 60, 255 - (_maxBrightness / 4));
    FastLED.show();
    delay(7);
  }
}


#endif

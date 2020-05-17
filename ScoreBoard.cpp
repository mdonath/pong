#ifndef __PONG_SCOREBOARD_CPP
#define __PONG_SCOREBOARD_CPP

#include "ScoreBoard.h"

void ScoreBoard::draw(Player *player1, Player *player2, const int brightness) {
  int halfNumberOfLeds = _numberOfLeds / 2;

  for (int i = 0; i < player1->getScore(); i++) {
    _field->setLed(halfNumberOfLeds - 1 - i,  CHSV(player1->color, 255, brightness));
  }

  for (int i = 0; i < player2->getScore(); i++) {
    _field->setLed(halfNumberOfLeds + i, CHSV(player2->color, 255, brightness));
  }
}

void ScoreBoard::blinkNewScore(Player *player, int brightness) {
  int pos = _numberOfLeds / 2;
  if (player->isLeftPlayer()) {
    pos -= player->getScore();
  } else {
    pos += player->getScore() - 1;
  }
  Color color = player->color;

  _field->draw(false);

  for (int i = 1; i <= 4; i++) {
    _field->setLed(pos, CHSV(color, 255, (i % 2) * brightness), true);  // blink LED 2 times (1-0-1-0)
    delay(300);
  }
}
#endif

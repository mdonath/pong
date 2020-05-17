#ifndef __PONG_SCOREBOARD_H
#define __PONG_SCOREBOARD_H

#include "Field.h"
#include "Player.h"

class Field;

class ScoreBoard {

  public:
    ScoreBoard(Field *field, int numberOfLeds) :
      _numberOfLeds(numberOfLeds),
      _field(field)
    {
    }

    void draw(Player *player1, Player *player2, const int brightness);
    void blinkNewScore(Player *player, const int brightness);

  private:
    Field *_field;
    int _numberOfLeds;

};

#endif

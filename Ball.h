#ifndef __PONG_BALL_H
#define __PONG_BALL_H

#include "Player.h"
#include "Field.h"

class Player;
class Field;

enum BallDirection : int {
  LEFT = -1,
  RIGHT = +1,
};

enum BallSpeedType : int {
  NORMAL = 1,
  NORMAL_BOOST = 15,
  SUPER_BOOST = 25,
};

class Ball {
  public:
    Ball(Field *field);

    bool isTimeToUpdate();
    void updatePosition();
    bool isPastEndZones();

    int position();
    BallDirection direction();
    BallSpeedType speedType();

    void setSpeed(int speed);
    BallSpeedType changeDirection(int gameSpeed, Player *player);

    void startAt(Player *player);

    void drawMovingBall();
    void drawMoving(int brightness);
    void drawTail(int brightness);
    void draw(Color color, const byte saturation, int brightness);

  private:
    const int speedMax = 1;

    Field *_field;

    int _maximumPosition;
    int _currentPosition;
    int _speed;
    BallSpeedType _speedType;

    BallDirection _direction = LEFT;

    unsigned long _previousMoveMillis;


    void changeSpeed(int gameSpeed, Player *player);
    bool isOutsideZones();

};

#endif

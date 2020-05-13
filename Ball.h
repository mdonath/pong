#ifndef __PONG_BALL_H
#define __PONG_BALL_H

#include "Player.h"

class Player;


class Ball {
  public:
    enum Direction {
      LEFT = -1,
      RIGHT = +1,
    };

    enum SpeedType {
      NORMAL = 1,
      NORMAL_BOOST = 15,
      SUPER_BOOST = 25,
    };

  public:

    void begin(int maximumPosition);
    void setSpeed(int speed);
    bool isTimeToUpdate();
    void updatePosition();
    int position() {
      return _currentPosition;
    }
    Direction direction() {
      return _direction;
    }
    SpeedType speedType() {
      return _speedType;
    }
    SpeedType changeDirection(int gameSpeed, Player *player);

    void startAt(Player *player);

    void drawMoving(CRGB *leds, int brightness);
    void drawTail(CRGB *leds, int brightness);
    void draw(CRGB *leds, Color color, const byte saturation, int brightness);

  private:
    const int speedMax = 1;

    int _maximumPosition;
    int _currentPosition;
    int _speed;
    SpeedType _speedType;

    Direction _direction = LEFT;

    unsigned long _previousMoveMillis;


    void changeSpeed(int gameSpeed, Player *player);
    bool isOutsideZones();

};

#endif

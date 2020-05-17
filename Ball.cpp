#ifndef __PONG_BALL_CPP
#define __PONG_BALL_CPP

#include <Arduino.h>
#include "Ball.h"

Ball::Ball(Field *field) :
  _field(field) {
  _maximumPosition = field->size();
}

void Ball::setSpeed(const int speed) {
  _speed = speed;
}


bool Ball::isTimeToUpdate() {
  bool result =  millis() - _previousMoveMillis > _speed;
  if (result) {
    _previousMoveMillis = millis();
  }
  return result;
}

bool Ball::isPastEndZones() {
  return _field->isPastEndZones(this);
}

void Ball::drawMovingBall() {
  _field->drawMovingBall(this);
}

void Ball::updatePosition() {
  _currentPosition += _direction;
}

int Ball::position() {
  return _currentPosition;
}
BallDirection Ball::direction() {
  return _direction;
}
BallSpeedType Ball::speedType() {
  return _speedType;
}

void Ball::startAt(Player * const player) {
  if (player->isLeftPlayer()) {
    _direction = RIGHT;
  } else if (player->isRightPlayer()) {
    _direction = LEFT;
  }
  _currentPosition = player->getHomePosition();
  _speedType = BallSpeedType::NORMAL;
}

BallSpeedType Ball::changeDirection(const int gameSpeed, Player *player) {
  _direction = _direction == BallDirection::LEFT ? BallDirection::RIGHT : BallDirection::LEFT;
  changeSpeed(gameSpeed, player);
  return _speedType;
}


void Ball::changeSpeed(const int gameSpeed, Player *player) {
  _speed = gameSpeed;

  if (player->isSuperBoost(this)) {
    // triggered on first or last segment ==> Super Boost
    _speed -= BallSpeedType::SUPER_BOOST;
    _speedType = SUPER_BOOST;
  } else if (player->isNormalBoost(this)) {
    // triggered on second or forelast segment ==> Normal Boost
    _speed -= BallSpeedType::NORMAL_BOOST;
    _speedType = NORMAL_BOOST;
  } else {
    _speedType = NORMAL;
  }

  // limit the maximum speed
  _speed = max(_speed, speedMax);

}


void Ball::draw(Color color, const byte saturation, int brightness) {
  _field->setLed(_currentPosition, CHSV(color, saturation, brightness));
}

void Ball::drawMoving(int brightness) {
  draw(0, 0, brightness);
  drawTail(brightness);
}

void Ball::drawTail(int brightness) {
  const int pos = _currentPosition;
  const BallDirection dir = _direction;
  switch (_speedType) {
    case  BallSpeedType::NORMAL_BOOST:
      _field->setLed(pos - 1 * dir, CHSV(Color::BOOST, 255, brightness * 0.75));
      break;
    case  BallSpeedType::SUPER_BOOST:
      _field->setLed(pos - 1 * dir, CHSV(Color::SUPERBOOST, 255, brightness * 0.75));
      _field->setLed(pos - 2 * dir, CHSV(Color::BOOST, 255, brightness * 0.66));
      break;
  }
}

#endif

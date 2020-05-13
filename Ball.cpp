#ifndef __PONG_BALL_CPP
#define __PONG_BALL_CPP

#include <Arduino.h>
#include "Ball.h"


void Ball::begin(const int maximumPosition) {
  this->_maximumPosition = maximumPosition;
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


void Ball::updatePosition() {
  _currentPosition += _direction;
}

void Ball::startAt(Player * const player) {
  if (player->isLeftPlayer()) {
    _direction = RIGHT;
  } else if (player->isRightPlayer()) {
    _direction = Direction::LEFT;
  }
  _currentPosition = player->getHomePosition();
  _speedType = SpeedType::NORMAL;
}

Ball::SpeedType Ball::changeDirection(const int gameSpeed, Player *player) {
  _direction = _direction == Direction::LEFT ? Direction::RIGHT : Direction::LEFT;
  changeSpeed(gameSpeed, player);
  return _speedType;
}


void Ball::changeSpeed(const int gameSpeed, Player *player) {
  _speed = gameSpeed;

  if (player->isSuperBoost(this)) {
    // triggered on first or last segment ==> Super Boost
    _speed -= SpeedType::SUPER_BOOST;
    _speedType = SUPER_BOOST;
  } else if (player->isNormalBoost(this)) {
    // triggered on second or forelast segment ==> Normal Boost
    _speed -= SpeedType::NORMAL_BOOST;
    _speedType = NORMAL_BOOST;
  } else {
    _speedType = NORMAL;
  }

  // limit the maximum speed
  _speed = max(_speed, speedMax);

}


void Ball::draw(CRGB *leds, Color color, const byte saturation, int brightness) {
  leds[_currentPosition] = CHSV(color, saturation, brightness);
}

void Ball::drawMoving(CRGB *leds, int brightness) {
  draw(leds, 0, 0, brightness);
  drawTail(leds, brightness);
}

void Ball::drawTail(CRGB *leds, int brightness) {
  const int pos = _currentPosition;
  const Ball::Direction dir = _direction;
  switch (_speedType) {
    case  Ball::SpeedType::NORMAL_BOOST:
      leds[pos - 1 * dir] = CHSV(Color::BOOST, 255, brightness * 0.75);
      break;
    case  Ball::SpeedType::SUPER_BOOST:
      leds[pos - 1 * dir] = CHSV(Color::SUPERBOOST, 255, brightness * 0.75);
      leds[pos - 2 * dir] = CHSV(Color::BOOST, 255, brightness * 0.66);
      break;
  }
}

#endif

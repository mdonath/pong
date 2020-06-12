#ifndef __PONG_ZONE_CPP
#define __PONG_ZONE_CPP

#include "Zone.h"

Player *Zone::getPlayer() {
  return _player;
}

void Zone::setPlayer(Player *player) {
  this->_player = player;
}

void Zone::setSetupMode() {
  setColor(Color::ENDZONE_SETUP);
}

void Zone::setGameMode() {
  setColor(Color::ENDZONE_GAME);
}

bool Zone::isInEndZone(int ballPosition) {
  return _length > 0
         ? (ballPosition >= _homePosition) && (ballPosition < _homePosition + _length)
         : (ballPosition > _homePosition +  _length) && (ballPosition <= _homePosition);
}

bool Zone::isPastEndZone(int ballPosition) {
  return _length > 0
         ? (ballPosition < _homePosition)
         : (ballPosition > _homePosition);
}

bool Zone::isNormalBoost(int ballPosition) {
  return abs(_homePosition - ballPosition) == 1;
}

bool Zone::isSuperBoost(int ballPosition) {
  return ballPosition == _homePosition;
}

void Zone::draw(int brightness, bool show) {
  if (_length > 0) {
    for (int i = _homePosition; i < _homePosition + _length; i++) {
      _field->setLed(i, CHSV(_color, 255, _enabled ? brightness : 0), show);
    }
  } else {
    for (int i = _homePosition + 1 + _length; i < _homePosition + 1; i++) {
      _field->setLed(i, CHSV(_color, 255, _enabled ? brightness : 0), show);
    }
  }
}

void Zone::indicateStart(int brightness) {
  for (int r = 0; r < 10; r++) {
    if (_length > 0) {
      for (int i = _homePosition - 1 + _length; i > _homePosition - 1; i--) {
        _field->setLed(i, CHSV(_color, 255, r % 2 ? 0 : brightness), true);
      }
    } else {
      for (int i = _homePosition + 1 + _length; i < _homePosition + 1; i++) {
        _field->setLed(i, CHSV(_color, 255, r % 2 ? 0 : brightness), true);
      }
    }
    delay(50);
  }
  draw(brightness, true);
}

#endif

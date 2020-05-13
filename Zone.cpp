#ifndef __PONG_ZONE_CPP
#define __PONG_ZONE_CPP

#include "Zone.h"

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
  return abs(_homePosition - ballPosition) == 0;
}


void Zone::draw(CRGB *leds, int brightness) {
  if (_length > 0) {
    for (int i = _homePosition; i < _homePosition + _length; i++) {
      leds[i] = CHSV(_color, 255, brightness);
    }
  } else {
    for (int i = _homePosition + 1 + _length; i < _homePosition + 1; i++) {
      leds[i] = CHSV(_color, 255, brightness);
    }
  }
}


#endif

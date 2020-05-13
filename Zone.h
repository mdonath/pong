#ifndef __PONG_ZONE_H
#define __PONG_ZONE_H

#include <Arduino.h>
#include <FastLED.h>
#include "Colors.h"


class Zone {
  public:

    Zone(int homePosition, int zoneLength) :
      _homePosition(homePosition),
      _length(zoneLength)
    {
    }

    bool isInEndZone(int ballPosition);
    bool isPastEndZone(int ballPosition);
    bool isNormalBoost(int ballPosition);
    bool isSuperBoost(int ballPosition);

    void draw(CRGB *leds, int brightness);

    void setColor(Color color) {
      _color = color;
    }

    void setEndZoneSize(int size) {
      _length = size;
    }

    int getHomePosition() {
      return _homePosition;
    }

  private:
    int _homePosition;
    int _length;
    int _color = Color::ENDZONE_GAME;

};

#endif

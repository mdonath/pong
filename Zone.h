#ifndef __PONG_ZONE_H
#define __PONG_ZONE_H

#include <Arduino.h>
#include <FastLED.h>
#include "Colors.h"
#include "Field.h"
#include "Player.h"

class Player;
class Field;

class Zone {
  public:

    Zone(Field *field, int homePosition, int zoneLength) :
      _field(field),
      _homePosition(homePosition),
      _length(zoneLength)
    {
      _enabled = true;
    }

    Player *getPlayer();
    void setPlayer(Player *player);

    void setSetupMode();
    void setGameMode();

    bool isInEndZone(int ballPosition);
    bool isPastEndZone(int ballPosition);
    bool isNormalBoost(int ballPosition);
    bool isSuperBoost(int ballPosition);

    void disable() {
      _enabled = false;
    }
    void enable() {
      _enabled = true;
    }
    void draw(int brightness, bool show = false);
    void indicateStart(int brightness);

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
    Field *_field;
    Player *_player;
    
    int _homePosition;
    int _length;
    int _color = Color::ENDZONE_GAME;
    bool _enabled;

};

#endif

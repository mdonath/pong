#ifndef __PONG_PLAYER_CPP
#define __PONG_PLAYER_CPP

#include "Player.h"


void Player::begin(Zone *zone) {
  pinMode(_buttonPin, INPUT_PULLUP);   // PINs for buttons
  _zone = zone;
}

void Player::setSetupMode() {
  _zone->setColor(Color::ENDZONE_SETUP);
}

void Player::setGameMode() {
  _zone->setColor(Color::ENDZONE_GAME);
}

void Player::drawZone(CRGB *leds, int brightness) {
  _zone->draw(leds, brightness);
}

int Player::getHomePosition() {
  return _zone->getHomePosition();
}

bool Player::hasButtonPressedInEndZone(Ball *const ball) {
  return _zone->isInEndZone(ball->position());
};

bool Player::isSuperBoost(Ball *ball) {
  return _zone->isSuperBoost(ball->position());
}
bool Player::isNormalBoost(Ball *ball) {
  return _zone->isNormalBoost(ball->position());

}

bool Player::isPastEndZone(Ball *ball) {
  return _zone->isPastEndZone(ball->position());
}


void Player::rememberPressed() {
  alreadyPressedButton = true;
}

bool Player::hasAlreadyPressedButton() {
  return alreadyPressedButton;
}

void Player::forgetPressed() {
  alreadyPressedButton = false;
}

void Player::reset() {
  _score = 0;
}

void Player::addPoint() {
  _score += 1;
}

void Player::waitForButtonPress() {
  while (buttonBounce(5) == false) {}
}

void Player::waitForButtonRelease() {
  while (buttonBounce(5)) {}
}

bool Player::isPressingButton() {
  return buttonBounce(5);
}

// function to debounce button (true == pressed, false == not pressed)
boolean Player::buttonBounce(const byte bounceTime) {
  boolean result = false;

  if (isButtonPressed()) {
    delay (bounceTime);
    if (isButtonPressed()) {
      result = true;
    }
  }
  return result;
}


bool Player::isButtonPressed() {
  return readButton() == LOW;
}


bool Player::isButtonReleased() {
  return readButton() == HIGH;
}


int Player::readButton() {
  return digitalRead(_buttonPin);
}


#endif

#ifndef __PONG_GAME_CPP
#define __PONG_GAME_CPP

#include "Game.h"
#include "Ball.h"
#include "Sound.h"

void Game::begin(Field *field, Player *player1, Player *player2, Sound *sound) {
  this->_field = field;
  this->_player1 = player1;
  this->_player2 = player2;

  randomSeed(analogRead(0));
  _currentPlayer = random(2) == 0 ? player1 : player2;

  _ball = new Ball();
  _ball->begin(_field->size());

  _sound = sound;
  _sound->begin();
}

Player *Game::getPlayer(byte number) {
  switch (number) {
    case 1:
      return _player1;
    case 2:
      return _player2;
  }
}

void Game::menu() {
  _field->clear();
  _field->showSetupMode();
  _field->draw(this);

  checkMenuBrightness();
  checkMenuStartGame();
}

void Game::checkMenuBrightness() {
  if (_player1->isPressingButton()) {
    _field->nextBrightness();
    _player1->waitForButtonRelease();
  }
}

void Game::checkMenuStartGame() {
  if (_player2->isPressingButton()) {
    _field->showGameMode();
    _active = true;
    _player2->waitForButtonRelease();

    start();
  }
}

void Game::start() {
  while (_active) {
    initializeGame();
    initializePlayers();

    gameLoop();
    checkScore();
    checkWinner();
  }
}


void Game::initializeGame() {
  _sound->playStartGame();
  _speed = startingGameSpeed;
  _ball->setSpeed(_speed);
  _player1->forgetPressed();
  _player2->forgetPressed();

  _field->drawDimmed(this);  // show gamefield with dimmed score
}


void Game::initializePlayers() {
  // set the player-settings -> wait for keypress to start game
  _field->drawBallAtPlayerAndWait(_ball, _currentPlayer);
  _sound->playBounce();
}


void Game::gameLoop() {
  while (true) {   // exit with break when a player scores

    if (_ball->isTimeToUpdate()) {
      _field->drawDimmed(false);
      _ball->updatePosition();
      if (_player1->isPastEndZone(_ball) || _player2->isPastEndZone(_ball)) {
        break;             // leave loop -> a player made a score
      }

      // generate ball (white)
      _field->drawMovingBall(_ball);
    }

    checkInput();
  }
}


// *** check if buttons pressed
void Game::checkInput() {
  checkPlayerButton(_player1, Ball::Direction::LEFT);
  checkPlayerButton(_player2, Ball::Direction::RIGHT);
}

void Game::checkPlayerButton(Player* const player, const Ball::Direction direction) {
  if (!player->hasAlreadyPressedButton() && player->isButtonPressed() && _ball->direction() == direction) {
    _field->rememberButtonPress(_ball, player);
    if (player->hasButtonPressedInEndZone(_ball)) {
      changeDirection(player);
    }
  }
}

void Game::changeDirection(Player *player) {
  _speed -= speedStep;
  Ball::SpeedType speedType = _ball->changeDirection(_speed, player);
  playBounceSound(speedType);
  player->forgetPressed();
}

void Game::playBounceSound(Ball::SpeedType speedType) {
  switch (speedType) {
    case Ball::SpeedType::NORMAL:
      _sound->playBounce();
      break;
    case Ball::SpeedType::NORMAL_BOOST:
      _sound->playSmash();
      break;
    case Ball::SpeedType::SUPER_BOOST:
      _sound->playSuperSmash();
      break;
  }
}

void Game::checkScore() {
  _field->forgetButtonPress();
  _sound->playScore();

  if (_ball->position() < _player1->getHomePosition()) {
    showScoringPlayer(_player2);
  } else if (_ball->position() > _player2->getHomePosition()) {
    showScoringPlayer(_player1);
  } else {
    // ???
  }
}

void Game::showScoringPlayer(Player* const player) {
  player->addPoint();

  _field->blinkNewScore(player);

  _currentPlayer = player;

  _field->draw(this);

  delay(1000);
}

void Game::checkWinner() {
  if (_player1->getScore() >= winRounds || _player2->getScore() >= winRounds) {
    // we have a winner!
    _active = false;

    _sound->playVictory();
    _field->showRainbow(_player1->getScore() > _player2->getScore());

    // reset all scores
    _player1->reset();
    _player2->reset();

    // next game starts loser
    _currentPlayer = _currentPlayer == _player1 ? _player2 : _player1;
  }
}

#endif

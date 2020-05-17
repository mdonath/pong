#ifndef __PONG_GAME_CPP
#define __PONG_GAME_CPP

#include "Game.h"
#include "Ball.h"
#include "Sound.h"


Game::Game(Field *field, Sound *sound, Player *player1, Player *player2) :
  _field(field),
  _player1(player1),
  _player2(player2),
  _sound(sound) {

  _field->setGame(this);
  _field->assignToZone1(_player1);
  _field->assignToZone2(_player2);

  _ball = new Ball(_field);

  randomSeed(analogRead(0));
  _currentPlayer = random(2) == 0 ? _player1 : _player2;
}

void Game::begin() {
  _sound->begin();
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
    _field->setupNextBrightness();
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
      if (_ball->isPastEndZones()) {
        // leave loop because a player made a score
        break;
      }

      // generate ball (white)
      _ball->drawMovingBall();
    }

    checkPlayerButtons();
  }
}

// *** check if buttons pressed
void Game::checkPlayerButtons() {
  checkPlayerButton(_player1, BallDirection::LEFT);
  checkPlayerButton(_player2, BallDirection::RIGHT);
}

void Game::checkPlayerButton(Player* const player, const BallDirection direction) {
  if (!player->hasAlreadyPressedButton() && player->isButtonPressed() && _ball->direction() == direction) {
    _field->rememberButtonPress(_ball, player);
    if (player->hasButtonPressedInEndZone(_ball)) {
      changeDirection(player);
    }
  }
}

void Game::changeDirection(Player *player) {
  _speed -= speedStep;
  BallSpeedType speedType = _ball->changeDirection(_speed, player);
  playBounceSound(speedType);
  player->forgetPressed();
}

void Game::playBounceSound(BallSpeedType speedType) {
  switch (speedType) {
    case BallSpeedType::NORMAL:
      _sound->playBounce();
      break;
    case BallSpeedType::NORMAL_BOOST:
      _sound->playSmash();
      break;
    case BallSpeedType::SUPER_BOOST:
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

void Game::showScoringPlayer(Player *player) {
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

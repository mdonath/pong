#ifndef __PONG_GAME_H
#define __PONG_GAME_H

#include "Player.h"
#include "Field.h"
#include "Ball.h"
#include "Sound.h"
#include "Colors.h"

class Field;
class Player;
class Ball;

/**
   Contains a field and two players.
*/
class Game {
  public:

    void begin(Field *field, Player *player1, Player *player2, Sound *sound);
    void menu();

    Player *getPlayer(byte number);

  private:
    const int winRounds         = 10; // x winning rounds for winning game
    const int startingGameSpeed = 50; // min game-speed
    const int speedMax          =  5; // max game-speed
    const int speedStep         =  1; // fasten up when change direction

    void checkMenuBrightness();
    void checkMenuStartGame();

    void start();
    void initializeGame();
    void initializePlayers();
    void gameLoop();
    void checkInput();
    void checkPlayerButton(Player *player, const Ball::Direction direction);
    void checkButtonPressedPosition();
    void changeDirection(Player *player);
    void playBounceSound(Ball::SpeedType speedType);
    void checkScore();
    void showScoringPlayer(Player *player);
    void checkWinner();

    boolean _active = false;
    int _speed;

    Ball *_ball;

    Field *_field;
    
    Player *_player1;
    Player *_player2;
    Player *_currentPlayer;
    
    Sound *_sound;
};

#endif

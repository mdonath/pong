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
enum BallDirection : int;
enum BallSpeedType : int;

/**
   Contains a field and two players.
*/
class Game {
  public:
    Game(Field *field, Sound *sound, Player *player1, Player *player2);
    void begin();
    void menu();

  private:
    const int winRounds         = 10; // x winning rounds for winning game
    const int startingGameSpeed = 50; // min game-speed
    const int speedMax          =  5; // max game-speed
    const int speedStep         =  1; // fasten up when change direction

    boolean _active = false;
    int _speed;

    Ball *_ball;
    Field *_field;
    
    Player *_player1;
    Player *_player2;
    Player *_currentPlayer;
    
    Sound *_sound;

    void checkMenuBrightness();
    void checkMenuStartGame();

    void start();
    void initializeGame();
    void initializePlayers();
    void gameLoop();
    void checkPlayerButtons();
    void checkPlayerButton(Player *player, const BallDirection direction);
    void checkButtonPressedPosition();
    void changeDirection(Player *player);
    void playBounceSound(BallSpeedType speedType);
    void checkScore();
    void showScoringPlayer(Player *player);
    void checkWinner();
};

#endif

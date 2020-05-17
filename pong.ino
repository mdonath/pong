/*
  =====================
  One-dimensional pong.
  =====================

  Derived from https://create.arduino.cc/projecthub/flyingangel/1d-pong-85e965.

  Changes:
  - Converted to C++
  - Removed code for player LEDs, the LED on the strip closest to the player lights up

  Hardware:
  - Board: Arduino Nano
  - Processor: ATmega328P (Old Bootloader)
  - Two arcade buttons
  - 1 m LED strip 60/m
  - a resistor
  - 1000 uF capacitor

  Setup:
  - Button player one on pin D7 shorts to GND
  - Button player two on pin D8 shorts to GND
  - NeoPixelstrip 5V, GND and a resistor between pin D9 and data in

  Game:
  - On start both player zones light up yellow. P1 button increases brightness, P2 button starts the game.
  - A player is randomly selected to begin the game and the LED closest to the player lights up in red (player 1) or green (player 2).
  - This player can shoot the ball by pressing the button.
  - If the opponent presses the button when the ball is in their zone, the ball bounces back to the other player.
  - If the opponent presses the button when the ball is outside their zone, the other player is awarded with a point.
  - Scored points are shown briefly in the middle of the playing field.
  - The first player reaching 10 points is the winner and is shown a rainbow pattern on their side of the field.
  - The game starts again and the loser is allowed to start a new game.
*/

#include "Player.h"
#include "Game.h"
#include "Sound.h"

#define NUMBER_OF_LEDS 60

#define BUZZER_PIN 4
#define PLAYER1_PIN 7
#define PLAYER2_PIN 8
#define LED_DATA_PIN 9

#define ZONE_LENGTH 6

Player player1(PLAYER1_PIN, Color::PLAYER1);
Player player2(PLAYER2_PIN, Color::PLAYER2);

Field field(NUMBER_OF_LEDS, ZONE_LENGTH);
Sound sound(BUZZER_PIN);

Game game(&field, &sound, &player1, &player2);

void setup() {
  Serial.begin(9600);

  player1.begin();
  player2.begin();
  field.begin<LED_DATA_PIN>();
  game.begin();
}

void loop() {
  game.menu();
}

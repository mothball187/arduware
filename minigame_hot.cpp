#include "minigame_hot.h"

float makeItHot_progress = 0;
bool makeItHot_newGame = true;
unsigned long makeItHot_timer = 0;
bool makeItHot_failedState = false;
bool makeItHot_successState = false;
unsigned long makeItHot_stateTimer = 0;

void doMakeItHotGame() {
  if (makeItHot_failedState) {
    arduboy.setCursor(50, 30);
    arduboy.print(F("FAIL!"));
    if (millis() - makeItHot_stateTimer >= 2000) {
      makeItHot_failedState = false;
      makeItHot_newGame = true;
      gameState = STATE_INTERMISSION;
    }
    return;
  }

  if (makeItHot_successState) {
    arduboy.setCursor(40, 30);
    arduboy.print(F("SUCCESS!"));
    if (millis() - makeItHot_stateTimer >= 2000) {
      makeItHot_successState = false;
      makeItHot_newGame = true;
      gameState = STATE_INTERMISSION;
    }
    return;
  }

  if (makeItHot_newGame) {
    makeItHot_progress = 0;
    makeItHot_timer = millis();
    makeItHot_newGame = false;
    makeItHot_failedState = false;
    makeItHot_successState = false;
  }

  // Calculate remaining time
  int time_elapsed = (millis() - makeItHot_timer) / 1000;
  int time_remaining = 6 - time_elapsed;

  // Title text
  arduboy.setCursor(14, 10);
  arduboy.print(F("Smash the A button!"));

  // Timer text
  arduboy.setCursor(16, 30);
  arduboy.print(time_remaining);
  arduboy.print(F("s"));

  // Thermometer outline
  int therm_x = 60;
  int therm_y = 20;
  int therm_w = 8;
  int therm_h = 32;

  // Bulb at the bottom
  int bulb_r = 6;
  int bulb_x = therm_x + (therm_w / 2);
  int bulb_y = therm_y + therm_h + 2;

  // Draw thermometer outline
  arduboy.drawRect(therm_x, therm_y, therm_w, therm_h, WHITE);
  arduboy.drawCircle(bulb_x, bulb_y, bulb_r, WHITE);
  // Clear the line between the bulb and the stem
  arduboy.drawLine(therm_x + 1, therm_y + therm_h, therm_x + therm_w - 2,
                   therm_y + therm_h, BLACK);

  // Handle Input
  if (arduboy.justPressed(A_BUTTON)) {
    makeItHot_progress +=
        4.5f; // Each press fills it up by this much percentage
  }

  // Constantly drain the thermometer
  makeItHot_progress -= 0.5f; // Drain rate

  if (makeItHot_progress < 0) {
    makeItHot_progress = 0;
  } else if (makeItHot_progress > 100) {
    makeItHot_progress = 100;
  }

  // Draw the filled portion of the thermometer
  // For the bulb, we can just fill it for simplicity, since progress starts
  // there
  arduboy.fillCircle(bulb_x, bulb_y, bulb_r - 1, WHITE);

  // Calculate the height of the filled stem based on progress
  int fill_h = (makeItHot_progress / 100.0f) * (therm_h - 1);
  if (fill_h > 0) {
    int fill_y = therm_y + therm_h - fill_h;
    arduboy.fillRect(therm_x + 1, fill_y, therm_w - 2, fill_h, WHITE);
  }

  // Win condition: fill it entirely before time runs out
  if (makeItHot_progress >= 100) {
    score += 15;
    turnOnLED(COLOR_GREEN);
    makeItHot_successState = true;
    makeItHot_stateTimer = millis();
    return;
  }

  // Lose condition: run out of time
  if (time_remaining <= 0) {
    turnOnLED(COLOR_RED);
    makeItHot_failedState = true;
    makeItHot_stateTimer = millis();
    return;
  }
}

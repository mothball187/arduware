#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduboy2.h>
#include <ArduboyTones.h>

// Extern declarations for global instances
extern Arduboy2 arduboy;
extern ArduboyTones sound;

// Extern declarations for global game state
extern int score;

const int MAX_X_POS = 128;
const int MAX_Y_POS = 64;

// --- STATE DEFINITIONS ---
enum GameState {
  STATE_SPLASH_SCREEN, // Initial state
  STATE_MAIN_MENU,     // Where the user selects an option
  STATE_INTERMISSION,
  STATE_GAMEPLAY,  // The main action screen
  STATE_SETTINGS,  // A simple options screen
  STATE_GAME_OVER, // End screen
  NUM_GAME_STATES  // Total count of states (must be last)
};

extern GameState gameState;

enum MiniGameState {
  GAME_ARROWS,
  GAME_SIMON,
  GAME_SPOTLIGHT,
  GAME_MAKE_IT_HOT,
  GAME_MARSHMALLOW_DROP,
  NUM_GAMES
};

extern bool DEBUG_MODE_ENABLED;
extern MiniGameState DEBUG_MINIGAME;

extern MiniGameState currentMiniGame;

// --- LED MANAGEMENT CONSTANTS ---
const uint8_t COLOR_GREEN = 0;
const uint8_t COLOR_RED = 1;
extern void turnOnLED(uint8_t color);

// --- BITMAPS ---
extern const unsigned char PROGMEM background[];
extern const uint8_t PROGMEM right_arrow[];
extern const uint8_t PROGMEM left_arrow[];
extern const uint8_t PROGMEM down_arrow[];
extern const uint8_t PROGMEM up_arrow[];
extern const uint8_t PROGMEM right_arrow_hollow[];
extern const uint8_t PROGMEM left_arrow_hollow[];
extern const uint8_t PROGMEM down_arrow_hollow[];
extern const uint8_t PROGMEM up_arrow_hollow[];
extern const uint8_t PROGMEM a_button[];
extern const uint8_t PROGMEM b_button[];
extern const uint8_t PROGMEM button_filled[];
extern const unsigned char PROGMEM bubbleburst[];
extern const unsigned char PROGMEM bubbleburst_mask[];
extern const unsigned char PROGMEM X[];
extern const unsigned char PROGMEM smiley_face[];

#endif

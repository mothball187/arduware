#include <Arduboy2.h>
#include <ArduboyTones.h>
#include <stdlib.h>
#include <time.h>
Arduboy2 arduboy;
ArduboyTones sound(arduboy.audio.enabled);

int score = 0;

const unsigned char PROGMEM background[] = {
    // width, height,
    8, 8, 0x81, 0x00, 0x12, 0x40, 0x04, 0x11, 0x00, 0x04,
};

const uint8_t PROGMEM right_arrow[] = {
    16,   16,   0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
    0xf8, 0xf0, 0xe0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x03, 0x03, 0x03, 0x03,
    0x03, 0x03, 0x03, 0x03, 0x1f, 0x0f, 0x07, 0x03, 0x01, 0x00,
};

const uint8_t PROGMEM left_arrow[] = {
    16,   16,   0x00, 0x80, 0xc0, 0xe0, 0xf0, 0xf8, 0xc0, 0xc0, 0xc0, 0xc0,
    0xc0, 0xc0, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x0f, 0x1f,
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x00, 0x00,
};

const uint8_t PROGMEM down_arrow[] = {
    16,   16,   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0xfc, 0xfc, 0xfc,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x0c, 0x1c,
    0x3f, 0x7f, 0x7f, 0x3f, 0x1c, 0x0c, 0x04, 0x00, 0x00, 0x00,
};

const uint8_t PROGMEM up_arrow[] = {
    16,   16,   0x00, 0x00, 0x00, 0x20, 0x30, 0x38, 0xfc, 0xfe, 0xfe, 0xfc,
    0x38, 0x30, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x3f, 0x3f, 0x3f, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

const uint8_t PROGMEM right_arrow_hollow[] = {
    16,   16,   0x00, 0x00, 0xc0, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
    0x78, 0x10, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x03, 0x02, 0x02, 0x02,
    0x02, 0x02, 0x02, 0x02, 0x1e, 0x08, 0x04, 0x02, 0x01, 0x00,
};

const uint8_t PROGMEM left_arrow_hollow[] = {
    16,   16,   0x00, 0x80, 0x40, 0x20, 0x10, 0x78, 0x40, 0x40, 0x40, 0x40,
    0x40, 0x40, 0x40, 0xc0, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x08, 0x1e,
    0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x03, 0x00, 0x00,
};

const uint8_t PROGMEM down_arrow_hollow[] = {
    16,   16,   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x04, 0x04, 0xfc,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x0c, 0x14,
    0x27, 0x40, 0x40, 0x27, 0x14, 0x0c, 0x04, 0x00, 0x00, 0x00,
};

const uint8_t PROGMEM up_arrow_hollow[] = {
    16,   16,   0x00, 0x00, 0x00, 0x20, 0x30, 0x28, 0xe4, 0x02, 0x02, 0xe4,
    0x28, 0x30, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x3f, 0x20, 0x20, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

const uint8_t PROGMEM a_button[] = {
    16,   16,   0xe0, 0x30, 0x18, 0x0c, 0x06, 0xe3, 0x31, 0x11, 0x11, 0x31,
    0xe3, 0x06, 0x0c, 0x18, 0x30, 0xe0, 0x03, 0x06, 0x0c, 0x18, 0x30, 0x67,
    0x41, 0x41, 0x41, 0x41, 0x67, 0x30, 0x18, 0x0c, 0x06, 0x03,
};

const uint8_t PROGMEM b_button[] = {
    16,   16,   0xe0, 0x30, 0x18, 0x0c, 0x06, 0x03, 0xf1, 0x91, 0x91, 0x91,
    0x63, 0x06, 0x0c, 0x18, 0x30, 0xe0, 0x03, 0x06, 0x0c, 0x18, 0x30, 0x60,
    0x47, 0x44, 0x44, 0x44, 0x63, 0x30, 0x18, 0x0c, 0x06, 0x03,
};

const uint8_t PROGMEM button_filled[] = {
    16,   16,   0xe0, 0xf0, 0xf8, 0xfc, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xfe, 0xfc, 0xf8, 0xf0, 0xe0, 0x03, 0x07, 0x0f, 0x1f, 0x3f, 0x7f,
    0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x3f, 0x1f, 0x0f, 0x07, 0x03,
};

const unsigned char PROGMEM bubbleburst[] = {

    // width, height,
    16, 16,
    // FRAME 00
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    // FRAME 01
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x40, 0x40, 0xc0, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x02,
    0x02, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    // FRAME 02
    0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x20, 0x20, 0x20, 0x20, 0xc0, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x04,
    0x04, 0x04, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00,
    // FRAME 03
    0x00, 0x00, 0x00, 0x00, 0xc0, 0x30, 0x10, 0x10, 0x10, 0x10, 0x30, 0xc0,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x0c, 0x08, 0x08,
    0x08, 0x08, 0x0c, 0x03, 0x00, 0x00, 0x00, 0x00,
    // FRAME 04
    0x00, 0x00, 0x00, 0xc0, 0x20, 0x10, 0x08, 0x08, 0x08, 0x08, 0x10, 0x20,
    0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x08, 0x10, 0x20, 0x20,
    0x20, 0x20, 0x10, 0x08, 0x07, 0x00, 0x00, 0x00,
    // FRAME 05
    0x00, 0x00, 0xe0, 0x10, 0x08, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x08,
    0x10, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x07, 0x08, 0x10, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x10, 0x08, 0x07, 0x00, 0x00,
    // FRAME 06
    0x00, 0xf0, 0x08, 0x04, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
    0x04, 0x08, 0xf0, 0x00, 0x00, 0x0f, 0x10, 0x20, 0x40, 0x40, 0x40, 0x40,
    0x40, 0x40, 0x40, 0x40, 0x20, 0x10, 0x0f, 0x00,
    // FRAME 07
    0x00, 0x02, 0x06, 0x04, 0x0c, 0x08, 0x00, 0x00, 0x07, 0x00, 0x10, 0x18,
    0x0c, 0x06, 0x02, 0x00, 0x01, 0x41, 0x21, 0x11, 0x11, 0x18, 0x00, 0x00,
    0xf0, 0x00, 0x00, 0x19, 0x31, 0x61, 0x41, 0x01

};

const unsigned char PROGMEM bubbleburst_mask[] = {

    // width, height,
    16, 16,
    // FRAME 00
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    // FRAME 01
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x40, 0x40, 0xc0, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x02,
    0x02, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    // FRAME 02
    0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x20, 0x20, 0x20, 0x20, 0xc0, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x04,
    0x04, 0x04, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00,
    // FRAME 03
    0x00, 0x00, 0x00, 0x00, 0xc0, 0x30, 0x10, 0x10, 0x10, 0x10, 0x30, 0xc0,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x0c, 0x08, 0x08,
    0x08, 0x08, 0x0c, 0x03, 0x00, 0x00, 0x00, 0x00,
    // FRAME 04
    0x00, 0x00, 0x00, 0xc0, 0x20, 0x10, 0x08, 0x08, 0x08, 0x08, 0x10, 0x20,
    0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x08, 0x10, 0x20, 0x20,
    0x20, 0x20, 0x10, 0x08, 0x07, 0x00, 0x00, 0x00,
    // FRAME 05
    0x00, 0x00, 0xe0, 0x10, 0x08, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x08,
    0x10, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x07, 0x08, 0x10, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x10, 0x08, 0x07, 0x00, 0x00,
    // FRAME 06
    0x00, 0xf0, 0x08, 0x04, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
    0x04, 0x08, 0xf0, 0x00, 0x00, 0x0f, 0x10, 0x20, 0x40, 0x40, 0x40, 0x40,
    0x40, 0x40, 0x40, 0x40, 0x20, 0x10, 0x0f, 0x00,
    // FRAME 07
    0x00, 0x02, 0x06, 0x04, 0x0c, 0x08, 0x00, 0x00, 0x07, 0x00, 0x10, 0x18,
    0x0c, 0x06, 0x02, 0x00, 0x01, 0x41, 0x21, 0x11, 0x11, 0x18, 0x00, 0x00,
    0xf0, 0x00, 0x00, 0x19, 0x31, 0x61, 0x41, 0x01

};

const unsigned char PROGMEM X[] = {

    // width, height,
    16, 16,
    // FRAME 00
    0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x80, 0x40, 0x20, 0x10,
    0x08, 0x04, 0x02, 0x01, 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01,
    0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80

};

const unsigned char PROGMEM smiley_face[] = {
    // width, height,
    16,   16,   0xe0, 0x18, 0x04, 0x02, 0x32, 0x31, 0x01, 0x01, 0x01, 0x01,
    0x31, 0x32, 0x02, 0x04, 0x18, 0xe0, 0x03, 0x0c, 0x11, 0x22, 0x24, 0x44,
    0x44, 0x44, 0x44, 0x44, 0x44, 0x24, 0x22, 0x11, 0x0c, 0x03,
};

int MAX_X_POS = 128;
int MAX_Y_POS = 64;

// --- STATE DEFINITIONS ---
// Define all the major scenes/screens in your game here.
enum GameState {
  STATE_SPLASH_SCREEN, // Initial state
  STATE_MAIN_MENU,     // Where the user selects an option
  STATE_INTERMISSION,
  STATE_GAMEPLAY,  // The main action screen
  STATE_SETTINGS,  // A simple options screen
  STATE_GAME_OVER, // End screen
  NUM_GAME_STATES  // Total count of states (must be last)
};

// Global state variable
GameState gameState = STATE_SPLASH_SCREEN;

// --- MENU MANAGEMENT (for STATE_MAIN_MENU) ---
enum MenuOption {
  MENU_START_GAME,
  MENU_SETTINGS,
  MENU_QUIT, // For simplicity, this will transition to the Game Over screen
  NUM_MENU_OPTIONS
};

enum MiniGameState {
  GAME_ARROWS,
  GAME_SIMON,
  GAME_SPOTLIGHT,
  GAME_MAKE_IT_HOT,
  GAME_MARSHMALLOW_DROP,
  NUM_GAMES
};

// --- DEBUG VARIABLES ---
bool DEBUG_MODE_ENABLED = true;
MiniGameState DEBUG_MINIGAME = GAME_MARSHMALLOW_DROP;

MenuOption currentMenuOption = MENU_START_GAME;
MiniGameState currentMiniGame =
    GAME_SIMON; // Initialized properly in doMainMenu

// --- HELPER FUNCTION DECLARATIONS ---
void doSplashScreen();
void doMainMenu();
void doSettings();
void doGameplay();
void doGameOver();
void checkTransition();
void doMakeItHotGame();
void doMarshmallowDropGame();

// --- LED MANAGEMENT ---
unsigned long ledTurnOnTime = 0;
bool isLedOn = false;

void turnOnLED(uint8_t color) {
  if (color == GREEN_LED) {
    arduboy.setRGBled(0, 255, 0);
    // High, short beep for success
    sound.tone(1046, 100);
  } else if (color == RED_LED) {
    arduboy.setRGBled(255, 0, 0);
    // Low, longer beep for failure
    sound.tone(130, 250);
  }
  isLedOn = true;
  ledTurnOnTime = millis();
}

void turnOffLED() {
  arduboy.setRGBled(0, 0, 0);
  isLedOn = false;
}

// --- ARDUINO SETUP ---
void setup() {
  arduboy.begin();
  arduboy.setFrameRate(30); // Use 30 FPS for stable state machine logic
  arduboy.initRandomSeed();
  arduboy.audio.on(); // explicitly force audio on
}

// --- ARDUINO LOOP: THE STATE MACHINE CORE ---
void loop() {
  if (!arduboy.nextFrame()) {
    return;
  }

  arduboy.clear();
  arduboy.pollButtons();

  // Check LED timeout (250ms now)
  if (isLedOn && (millis() - ledTurnOnTime >= 250)) {
    turnOffLED();
  }

  // The main switch handles which scene's logic to execute
  switch (gameState) {
  case STATE_SPLASH_SCREEN:
    doSplashScreen();
    break;
  case STATE_MAIN_MENU:
    doMainMenu();
    break;
  case STATE_INTERMISSION:
    doIntermission();
    break;
  case STATE_GAMEPLAY:
    doGameplay();
    break;
  case STATE_SETTINGS:
    doSettings();
    break;
  case STATE_GAME_OVER:
    doGameOver();
    break;
  default:
    // Should never happen, but useful for debugging
    arduboy.print("ERROR STATE");
    break;
  }

  // Always display the buffer after the scene logic has finished drawing
  arduboy.display();
}

// --- MINI GAMES ---

// --- ARROWS GAME ---
unsigned long arrowsGame_lastSpawnTime = 0;
bool arrowsGame_shouldSpawn = true;
int16_t arrowsGame_spawnPos[] = {-1, -1};
int16_t arrowsGame_leftX = 5;
int16_t arrowsGame_rightX = 25;
int16_t arrowsGame_upX = 45;
int16_t arrowsGame_downX = 65;
int16_t arrowsGame_aX = 85;
int16_t arrowsGame_bX = 105;
int16_t arrowsGame_targetY = 42;
int16_t arrowsGame_target = 0;
int16_t arrowsGame_bubblePos[] = {-1, -1, 0};
int16_t arrowsGame_XPos[] = {-1, -1, 0};
int16_t arrowsGame_spawnTotal = 0;
int16_t arrowsGame_numArrows = 6;
void arrowsGameAnimateSprites() {
  if (arrowsGame_bubblePos[0] != -1) {
    Sprites::drawExternalMask(arrowsGame_bubblePos[0], arrowsGame_bubblePos[1],
                              bubbleburst, &bubbleburst_mask[2],
                              arrowsGame_bubblePos[2], arrowsGame_bubblePos[2]);
    arrowsGame_bubblePos[2]++;
    if (arrowsGame_bubblePos[2] >= 8) {
      arrowsGame_bubblePos[2] = 0;
      arrowsGame_bubblePos[0] = -1;
      arrowsGame_bubblePos[1] = -1;
    }
  }

  if (arrowsGame_XPos[0] != -1) {
    Sprites::drawExternalMask(arrowsGame_XPos[0], arrowsGame_XPos[1], X, &X[2],
                              0, 0);
    arrowsGame_XPos[2]++;
    if (arrowsGame_XPos[2] >= 5) {
      arrowsGame_XPos[2] = 0;
      arrowsGame_XPos[0] = -1;
      arrowsGame_XPos[1] = -1;
    }
  }
}
void arrowsGameSpawn(int16_t x) {
  arrowsGame_spawnPos[0] = x;
  arrowsGame_spawnPos[1] = 0;
  arrowsGame_shouldSpawn = false;
  arrowsGame_spawnTotal++;
}
void arrowsGameDespawn() {
  arrowsGame_spawnPos[0] = -1;
  arrowsGame_spawnPos[1] = -1;
  arrowsGame_shouldSpawn = true;
}
void arrowsGameSpawnBubble() {
  arrowsGame_bubblePos[0] = arrowsGame_spawnPos[0];
  arrowsGame_bubblePos[1] = arrowsGame_spawnPos[1];
  arrowsGame_bubblePos[2] = 0;
}
void arrowsGameSpawnX() {
  arrowsGame_XPos[0] = arrowsGame_spawnPos[0];
  arrowsGame_XPos[1] = arrowsGame_spawnPos[1];
  arrowsGame_XPos[2] = 0;
}
void arrowsGameHit() {
  score += 10;
  arrowsGameSpawnBubble();
  arrowsGameDespawn();
}

void doArrowsGame() {
  const uint8_t *spawnBmp;
  // char tim[20];
  if (arrowsGame_spawnTotal >= arrowsGame_numArrows &&
      arrowsGame_spawnPos[0] == -1 && arrowsGame_bubblePos[0] == -1 &&
      arrowsGame_XPos[0] == -1) {
    arrowsGameDespawn();
    arrowsGame_spawnTotal = 0;
    arrowsGame_lastSpawnTime = 0;
    gameState = STATE_INTERMISSION;
    return;
  }

  // spawning time
  if (arrowsGame_spawnTotal < arrowsGame_numArrows) {
    if (!arrowsGame_lastSpawnTime) {
      arrowsGame_lastSpawnTime = millis() / 1000;
      // snprintf(tim, 20, "time: %d", lastSpawnTime);
      // Serial.println(tim);
    } else if (arrowsGame_shouldSpawn &&
               millis() / 1000 - arrowsGame_lastSpawnTime > 0) {
      arrowsGame_lastSpawnTime = millis() / 1000;
      arrowsGame_target = random(6);
      switch (arrowsGame_target) {
      case 0:
        arrowsGameSpawn(arrowsGame_leftX);
        spawnBmp = left_arrow;
        break;
      case 1:
        arrowsGameSpawn(arrowsGame_rightX);
        spawnBmp = right_arrow;
        break;
      case 2:
        arrowsGameSpawn(arrowsGame_upX);
        spawnBmp = up_arrow;
        break;
      case 3:
        arrowsGameSpawn(arrowsGame_downX);
        spawnBmp = down_arrow;
        break;
      case 4:
        arrowsGameSpawn(arrowsGame_bX);
        spawnBmp = b_button;
        break;
      case 5:
        arrowsGameSpawn(arrowsGame_aX);
        spawnBmp = a_button;
        break;
      default:
        arrowsGameSpawn(arrowsGame_leftX);
        spawnBmp = left_arrow;
        break;
      }
      // Serial.println(F("time up!"));
    }
  }

  // draw the timing target buttons
  Sprites::drawExternalMask(arrowsGame_leftX, arrowsGame_targetY,
                            left_arrow_hollow, &left_arrow[2], 0, 0);
  Sprites::drawExternalMask(arrowsGame_rightX, arrowsGame_targetY,
                            right_arrow_hollow, &right_arrow[2], 0, 0);
  Sprites::drawExternalMask(arrowsGame_upX, arrowsGame_targetY, up_arrow_hollow,
                            &up_arrow[2], 0, 0);
  Sprites::drawExternalMask(arrowsGame_downX, arrowsGame_targetY,
                            down_arrow_hollow, &down_arrow[2], 0, 0);
  Sprites::drawExternalMask(arrowsGame_bX, arrowsGame_targetY, b_button,
                            &button_filled[2], 0, 0);
  Sprites::drawExternalMask(arrowsGame_aX, arrowsGame_targetY, a_button,
                            &button_filled[2], 0, 0);

  // draw the spawns
  if (arrowsGame_spawnPos[0] >= 0) {
    Sprites::drawExternalMask(arrowsGame_spawnPos[0], arrowsGame_spawnPos[1],
                              spawnBmp, spawnBmp + 2, 0, 0);
    arrowsGame_spawnPos[1] += 2;
    if (arrowsGame_spawnPos[1] >= MAX_Y_POS) {
      arrowsGameDespawn();
    }
  }

  // light up the button presses, do collision detection
  if (arduboy.justPressed(LEFT_BUTTON)) {
    Sprites::drawExternalMask(arrowsGame_leftX, arrowsGame_targetY, left_arrow,
                              &left_arrow[2], 0, 0);
    if (arrowsGame_spawnPos[0] == arrowsGame_leftX &&
        abs(arrowsGame_spawnPos[1] - 3 - arrowsGame_targetY) <= 5) {
      turnOnLED(GREEN_LED);
      arrowsGameHit();
    } else {
      turnOnLED(RED_LED);
      arrowsGameSpawnX();
      arrowsGameDespawn();
    }
  } else if (arduboy.justPressed(RIGHT_BUTTON)) {
    Sprites::drawExternalMask(arrowsGame_rightX, arrowsGame_targetY,
                              right_arrow, &right_arrow[2], 0, 0);
    if (arrowsGame_spawnPos[0] == arrowsGame_rightX &&
        abs(arrowsGame_spawnPos[1] - 3 - arrowsGame_targetY) <= 5) {
      turnOnLED(GREEN_LED);
      arrowsGameHit();
    } else {
      turnOnLED(RED_LED);
      arrowsGameSpawnX();
      arrowsGameDespawn();
    }
  } else if (arduboy.justPressed(UP_BUTTON)) {
    Sprites::drawExternalMask(arrowsGame_upX, arrowsGame_targetY, up_arrow,
                              &up_arrow[2], 0, 0);
    if (arrowsGame_spawnPos[0] == arrowsGame_upX &&
        abs(arrowsGame_spawnPos[1] - 3 - arrowsGame_targetY) <= 5) {
      turnOnLED(GREEN_LED);
      arrowsGameHit();
    } else {
      turnOnLED(RED_LED);
      arrowsGameSpawnX();
      arrowsGameDespawn();
    }
  } else if (arduboy.justPressed(DOWN_BUTTON)) {
    Sprites::drawExternalMask(arrowsGame_downX, arrowsGame_targetY, down_arrow,
                              &down_arrow[2], 0, 0);
    if (arrowsGame_spawnPos[0] == arrowsGame_downX &&
        abs(arrowsGame_spawnPos[1] - 3 - arrowsGame_targetY) <= 5) {
      turnOnLED(GREEN_LED);
      arrowsGameHit();
    } else {
      turnOnLED(RED_LED);
      arrowsGameSpawnX();
      arrowsGameDespawn();
    }
  } else if (arduboy.justPressed(B_BUTTON)) {
    Sprites::drawExternalMask(arrowsGame_bX, arrowsGame_targetY, button_filled,
                              &button_filled[2], 0, 0);
    if (arrowsGame_spawnPos[0] == arrowsGame_bX &&
        abs(arrowsGame_spawnPos[1] - 3 - arrowsGame_targetY) <= 5) {
      turnOnLED(GREEN_LED);
      arrowsGameHit();
    } else {
      turnOnLED(RED_LED);
      arrowsGameSpawnX();
      arrowsGameDespawn();
    }
  } else if (arduboy.justPressed(A_BUTTON)) {
    Sprites::drawExternalMask(arrowsGame_aX, arrowsGame_targetY, button_filled,
                              &button_filled[2], 0, 0);
    if (arrowsGame_spawnPos[0] == arrowsGame_aX &&
        abs(arrowsGame_spawnPos[1] - 3 - arrowsGame_targetY) <= 5) {
      turnOnLED(GREEN_LED);
      arrowsGameHit();
    } else {
      turnOnLED(RED_LED);
      arrowsGameSpawnX();
      arrowsGameDespawn();
    }
  }
  arrowsGameAnimateSprites();
}

// --- SIMON ---
uint16_t simonGame_patternCount = 5;
uint16_t simonGame_upPos[] = {40, 20};
uint16_t simonGame_downPos[] = {40, 40};
uint16_t simonGame_leftPos[] = {30, 30};
uint16_t simonGame_rightPos[] = {50, 30};
uint16_t simonGame_APos[] = {70, 30};
uint16_t simonGame_BPos[] = {90, 30};
uint16_t simonGame_pattern[5];
bool simonGame_newGame = true;
int simonGame_timer = 0;
uint16_t simonGame_prev = 6;
uint16_t simonGame_playerIdx = 0;
uint16_t simonGame_playTimeSeconds = 10;

void simonGameLightUp(uint16_t idx) {
  switch (idx) {
  case 0:
    Sprites::drawExternalMask(simonGame_leftPos[0], simonGame_leftPos[1],
                              left_arrow, &left_arrow[2], 0, 0);
    break;
  case 1:
    Sprites::drawExternalMask(simonGame_rightPos[0], simonGame_rightPos[1],
                              right_arrow, &right_arrow[2], 0, 0);
    break;
  case 2:
    Sprites::drawExternalMask(simonGame_upPos[0], simonGame_upPos[1], up_arrow,
                              &up_arrow[2], 0, 0);
    break;
  case 3:
    Sprites::drawExternalMask(simonGame_downPos[0], simonGame_downPos[1],
                              down_arrow, &down_arrow[2], 0, 0);
    break;
  case 4:
    Sprites::drawExternalMask(simonGame_APos[0], simonGame_APos[1],
                              button_filled, &button_filled[2], 0, 0);
    break;
  case 5:
    Sprites::drawExternalMask(simonGame_BPos[0], simonGame_BPos[1],
                              button_filled, &button_filled[2], 0, 0);
    break;
  default:
    break;
  }
}

bool simonGame_failedState = false;
int simonGame_failedTime = 0;

void doSimonGame() {
  if (simonGame_failedState) {
    arduboy.setCursor(50, 30);
    arduboy.print(F("FAIL!"));
    if (millis() / 1000 - simonGame_failedTime >= 2) {
      simonGame_failedState = false;
      simonGame_newGame = true;
      gameState = STATE_INTERMISSION;
    }
    return;
  }

  uint16_t pattern_idx;
  uint16_t seconds_elapsed;
  uint16_t cur;
  // new game, generate the pattern
  if (simonGame_newGame) {
    for (int i = 0; i < simonGame_patternCount; i++) {
      cur = random(6);
      while (cur == simonGame_prev) {
        cur = random(6);
      }
      simonGame_pattern[i] = cur;
      simonGame_prev = cur;
    }
    simonGame_newGame = false;
    simonGame_timer = millis() / 1000;
    simonGame_playerIdx = 0;
  }
  // draw the buttons
  Sprites::drawExternalMask(simonGame_leftPos[0], simonGame_leftPos[1],
                            left_arrow_hollow, &left_arrow[2], 0, 0);
  Sprites::drawExternalMask(simonGame_rightPos[0], simonGame_rightPos[1],
                            right_arrow_hollow, &right_arrow[2], 0, 0);
  Sprites::drawExternalMask(simonGame_upPos[0], simonGame_upPos[1],
                            up_arrow_hollow, &up_arrow[2], 0, 0);
  Sprites::drawExternalMask(simonGame_downPos[0], simonGame_downPos[1],
                            down_arrow_hollow, &down_arrow[2], 0, 0);
  Sprites::drawExternalMask(simonGame_APos[0], simonGame_APos[1], a_button,
                            &button_filled[2], 0, 0);
  Sprites::drawExternalMask(simonGame_BPos[0], simonGame_BPos[1], b_button,
                            &button_filled[2], 0, 0);
  seconds_elapsed = millis() / 1000 - simonGame_timer;

  // player's turn
  uint16_t pressed = simonGame_patternCount + 1;
  if (seconds_elapsed >= simonGame_patternCount) {
    if (arduboy.justPressed(LEFT_BUTTON)) {
      pressed = 0;
    } else if (arduboy.justPressed(RIGHT_BUTTON)) {
      pressed = 1;
    } else if (arduboy.justPressed(UP_BUTTON)) {
      pressed = 2;
    } else if (arduboy.justPressed(DOWN_BUTTON)) {
      pressed = 3;
    } else if (arduboy.justPressed(A_BUTTON)) {
      pressed = 4;
    } else if (arduboy.justPressed(B_BUTTON)) {
      pressed = 5;
    }

    simonGameLightUp(pressed);

    if (pressed == simonGame_pattern[simonGame_playerIdx]) {
      score += 10;
      simonGame_playerIdx++;
      turnOnLED(GREEN_LED);
    } else if (pressed != simonGame_patternCount + 1) {
      turnOnLED(RED_LED);
      simonGame_failedState = true;
      simonGame_failedTime = millis() / 1000;
      return;
    }

    // time over or player got em all
    if (seconds_elapsed >= simonGame_patternCount + simonGame_playTimeSeconds ||
        simonGame_playerIdx >= simonGame_patternCount) {
      simonGame_newGame = true;
      gameState = STATE_INTERMISSION;
    }
    return;
  }

  // first play the pattern
  pattern_idx = simonGame_pattern[seconds_elapsed];
  simonGameLightUp(pattern_idx);
}

// --- SPOTLIGHT GAME ---
int16_t spotlightGame_slX = 64;
int16_t spotlightGame_slY = 32;
int16_t spotlightGame_fX = 0;
int16_t spotlightGame_fY = 0;
bool spotlightGame_newGame = true;
unsigned long spotlightGame_timer = 0;
unsigned long spotlightGame_overlapTime = 0;
bool spotlightGame_wasOverlapping = false;

void doSpotlightGame() {
  if (spotlightGame_newGame) {
    // Spawn smiley face
    spotlightGame_fX = random(0, 112); // Smiley top-left X
    spotlightGame_fY = random(0, 48);  // Smiley top-left Y

    // Spawn spotlight centered specifically over the smiley face
    // The smiley is 16x16, so its center is fX + 8, fY + 8
    spotlightGame_slX = spotlightGame_fX + 8;
    spotlightGame_slY = spotlightGame_fY + 8;

    spotlightGame_timer = millis();
    spotlightGame_overlapTime = 0;
    spotlightGame_wasOverlapping = false;
    spotlightGame_newGame = false;
  }

  // Input Movement
  int16_t speed = 2;
  if (arduboy.pressed(LEFT_BUTTON)) {
    spotlightGame_slX -= speed;
  }
  if (arduboy.pressed(RIGHT_BUTTON)) {
    spotlightGame_slX += speed;
  }
  if (arduboy.pressed(UP_BUTTON)) {
    spotlightGame_slY -= speed;
  }
  if (arduboy.pressed(DOWN_BUTTON)) {
    spotlightGame_slY += speed;
  }

  // Keep spotlight on screen
  if (spotlightGame_slX < 16)
    spotlightGame_slX = 16;
  if (spotlightGame_slX > 112)
    spotlightGame_slX = 112;
  if (spotlightGame_slY < 16)
    spotlightGame_slY = 16;
  if (spotlightGame_slY > 48)
    spotlightGame_slY = 48;

  // Draw the white spotlight
  arduboy.fillCircle(spotlightGame_slX, spotlightGame_slY, 16, WHITE);

  // Draw the smiley face in BLACK so it's only visible inside the white
  // spotlight
  arduboy.drawBitmap(spotlightGame_fX, spotlightGame_fY, smiley_face + 2, 16,
                     16, BLACK);

  // Check overlap: "overlaps at all" -> distance from rect to circle center <=
  // radius
  int16_t testX = spotlightGame_slX;
  int16_t testY = spotlightGame_slY;

  if (spotlightGame_slX < spotlightGame_fX)
    testX = spotlightGame_fX;
  else if (spotlightGame_slX > spotlightGame_fX + 16)
    testX = spotlightGame_fX + 16;

  if (spotlightGame_slY < spotlightGame_fY)
    testY = spotlightGame_fY;
  else if (spotlightGame_slY > spotlightGame_fY + 16)
    testY = spotlightGame_fY + 16;

  int16_t distX = spotlightGame_slX - testX;
  int16_t distY = spotlightGame_slY - testY;
  int32_t distanceSquared = (int32_t)(distX * distX) + (int32_t)(distY * distY);

  bool currentOverlap = (distanceSquared <= (16 * 16));

  if (currentOverlap) {
    if (!spotlightGame_wasOverlapping) {
      spotlightGame_overlapTime = millis();
      spotlightGame_wasOverlapping = true;
    } else {
      // Every 500ms, add 10 points
      if (millis() - spotlightGame_overlapTime >= 500) {
        score += 10;
        sound.tone(1046, 100);
        spotlightGame_overlapTime = millis();
      }
    }
    arduboy.setRGBled(0, 255, 0); // Green

    static int16_t evadeVX = 0;
    static int16_t evadeVY = 0;
    static int evadeTimer = 0;

    // Averages 1.33, faster than base 1 but slower than 1.5
    int evasionSpeed = 1;
    if (random(3) == 0) {
      evasionSpeed = 2;
    }

    if (evadeTimer > 0) {
      evadeTimer--;
    } else {
      // Basic evasion: try to move away from the center of the spotlight
      evadeVX = 0;
      evadeVY = 0;
      if (spotlightGame_fX < spotlightGame_slX)
        evadeVX = -evasionSpeed;
      if (spotlightGame_fX > spotlightGame_slX)
        evadeVX = evasionSpeed;
      if (spotlightGame_fY < spotlightGame_slY)
        evadeVY = -evasionSpeed;
      if (spotlightGame_fY > spotlightGame_slY)
        evadeVY = evasionSpeed;

      // Add a bit of random wiggle
      if (random(2) == 0)
        evadeVX += random(-1, 2);
      if (random(2) == 0)
        evadeVY += random(-1, 2);
    }

    int nextX = spotlightGame_fX + evadeVX;
    int nextY = spotlightGame_fY + evadeVY;

    // Check if moving this way hits a border
    if (nextX <= 0 || nextX >= 112 || nextY <= 0 || nextY >= 48) {
      // Choose a random vector to continue evasion, avoiding the border
      evadeVX = random(-2, 3); // -2 to 2
      evadeVY = random(-2, 3);

      if (nextX <= 0)
        evadeVX = random(1, 4); // Move right
      if (nextX >= 112)
        evadeVX = random(-3, 0); // Move left
      if (nextY <= 0)
        evadeVY = random(1, 4); // Move down
      if (nextY >= 48)
        evadeVY = random(-3, 0); // Move up

      // Hold this evasion vector for a bit so it doesn't get stuck again
      // immediately
      evadeTimer = random(10, 30);
    }

    spotlightGame_fX += evadeVX;
    spotlightGame_fY += evadeVY;

    // Keep inside screen bounds
    if (spotlightGame_fX < 0)
      spotlightGame_fX = 0;
    if (spotlightGame_fX > 112)
      spotlightGame_fX = 112;
    if (spotlightGame_fY < 0)
      spotlightGame_fY = 0;
    if (spotlightGame_fY > 48)
      spotlightGame_fY = 48;

  } else {
    spotlightGame_wasOverlapping = false;
    arduboy.setRGBled(255, 0, 0); // Red
  }

  // 6-second timer check
  if (millis() - spotlightGame_timer >= 6000) {
    spotlightGame_newGame = true;
    arduboy.setRGBled(0, 0, 0); // Turn off LED
    gameState = STATE_INTERMISSION;
  }
}

// --- MAKE IT HOT GAME ---
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
    turnOnLED(GREEN_LED);
    makeItHot_successState = true;
    makeItHot_stateTimer = millis();
    return;
  }

  // Lose condition: run out of time
  if (time_remaining <= 0) {
    turnOnLED(RED_LED);
    makeItHot_failedState = true;
    makeItHot_stateTimer = millis();
    return;
  }
}

// --- MARSHMALLOW DROP GAME ---
struct Marshmallow {
  float x;
  float y;
  float speed;
  bool active;
};

int16_t md_mugX = 56;
const int md_mugW = 16;
const int md_mugH = 12;

Marshmallow md_marshmallows[6];
int md_spawnedCount = 0;
int md_resolvedCount = 0;
unsigned long md_lastSpawnTime = 0;
unsigned long md_nextSpawnDelay = 0;

bool md_newGame = true;
unsigned long md_endTimer = 0;

void doMarshmallowDropGame() {
  if (md_newGame) {
    md_mugX = 56;
    md_spawnedCount = 0;
    md_resolvedCount = 0;
    md_lastSpawnTime = millis();
    md_nextSpawnDelay = random(500, 1501); // Initial spawn delay 0.5s - 1.5s
    md_endTimer = 0;
    for (int i = 0; i < 6; i++) {
      md_marshmallows[i].active = false;
    }
    md_newGame = false;
  }

  // Handle endgame state
  if (md_resolvedCount >= 6) {
    md_newGame = true;
    gameState = STATE_INTERMISSION;
    return;
  }

  // Mug Input (continuous)
  if (arduboy.pressed(LEFT_BUTTON)) {
    md_mugX -= 2;
  }
  if (arduboy.pressed(RIGHT_BUTTON)) {
    md_mugX += 2;
  }

  // Wrap-around Mug
  if (md_mugX < -md_mugW + 1) {
    md_mugX = 127;
  } else if (md_mugX > 127) {
    md_mugX = -md_mugW + 1;
  }

  // Draw Mug
  int mugY = 64 - md_mugH;
  // Left edge
  arduboy.drawLine(md_mugX, mugY + 1, md_mugX, 63, WHITE);
  // Right edge
  arduboy.drawLine(md_mugX + md_mugW - 1, mugY + 1, md_mugX + md_mugW - 1, 63,
                   WHITE);
  // Bottom edge
  arduboy.drawLine(md_mugX, 63, md_mugX + md_mugW - 1, 63, WHITE);
  // Lip of the mug (extends slightly past the edges)
  arduboy.drawLine(md_mugX - 2, mugY, md_mugX + md_mugW + 1, mugY, WHITE);
  // Handle on the left side
  arduboy.drawRect(md_mugX - 4, mugY + 3, 4, 6, WHITE);

  // Animated steam
  int yOffset = (arduboy.frameCount / 2) % 4;
  for (int i = 0; i < 3; i++) {
    int steamX = md_mugX + 4 + (i * 4);
    int steamPhase = (arduboy.frameCount / 6 + i) % 2;
    int sY = mugY - 2 - yOffset;

    if (steamPhase == 0) {
      arduboy.drawLine(steamX, sY, steamX + 1, sY - 3, WHITE);
      arduboy.drawLine(steamX + 1, sY - 4, steamX, sY - 7, WHITE);
    } else {
      arduboy.drawLine(steamX + 1, sY, steamX, sY - 3, WHITE);
      arduboy.drawLine(steamX, sY - 4, steamX + 1, sY - 7, WHITE);
    }
  }

  // Spawning logic
  if (md_spawnedCount < 6 &&
      (millis() - md_lastSpawnTime >= md_nextSpawnDelay)) {
    // Find an inactive marshmallow to spawn
    for (int i = 0; i < 6; i++) {
      if (!md_marshmallows[i].active) {
        md_marshmallows[i].active = true;
        md_marshmallows[i].x = random(0, 128 - 4); // 4 is marshmallow width
        md_marshmallows[i].y = -4; // Spawn slightly above screen
        md_marshmallows[i].speed =
            random(5, 16) / 10.0f; // 0.5 to 1.5 pixels per frame

        md_spawnedCount++;
        md_lastSpawnTime = millis();
        // Wait 0.5 to 1.5 seconds before spawning next
        if (md_spawnedCount < 6) {
          md_nextSpawnDelay = random(500, 1501);
        }
        break; // Only spawn one this frame
      }
    }
  }

  // Marshmallow Update & Draw
  for (int i = 0; i < 6; i++) {
    if (md_marshmallows[i].active) {
      md_marshmallows[i].y += md_marshmallows[i].speed;

      int mX = (int)md_marshmallows[i].x;
      int mY = (int)md_marshmallows[i].y;

      // Draw marshmallow (solid rect taller than wide, e.g. 4x6)
      arduboy.fillRect(mX, mY, 4, 6, WHITE);

      // Collision Check (AABB with the opening of the mug)
      // The "catching" area is roughly the top of the mug
      if (mY + 6 >= mugY && mY < 64 && mX + 4 > md_mugX &&
          mX < md_mugX + md_mugW) {
        // Caught!
        score += 10;
        turnOnLED(GREEN_LED);
        md_marshmallows[i].active = false;
        md_resolvedCount++;
      }
      // Missed (reached bottom)
      else if (mY >= 64) {
        turnOnLED(RED_LED);
        md_marshmallows[i].active = false;
        md_resolvedCount++;
      }
    }
  }
}

// --- STATE IMPLEMENTATION FUNCTIONS ---

void doSplashScreen() {
  arduboy.setCursor(20, 20);
  arduboy.print(F("ELENA'S GAME"));
  arduboy.setCursor(10, 40);
  arduboy.print(F("PRESS A/B TO START"));

  // Transition logic for this state: wait for a button press
  if (arduboy.justPressed(A_BUTTON | B_BUTTON)) {
    gameState = STATE_MAIN_MENU;
    // Optionally reset menu cursor here if needed
    currentMenuOption = MENU_START_GAME;
  }
}

int intermissionTime = 0;
void doIntermission() {
  turnOffLED(); // Turn off LED
  if (intermissionTime == 0) {
    intermissionTime = millis() / 1000;
  }
  arduboy.setCursor(25, MAX_Y_POS / 2 - 10);
  arduboy.print(F("Intermission"));
  switch (millis() / 1000 - intermissionTime) {
  case 0:
    arduboy.setCursor(MAX_X_POS / 2, MAX_Y_POS / 2);
    arduboy.print(F("3"));
    break;
  case 1:
    arduboy.setCursor(MAX_X_POS / 2, MAX_Y_POS / 2);
    arduboy.print(F("2"));
    break;
  case 2:
    arduboy.setCursor(MAX_X_POS / 2, MAX_Y_POS / 2);
    arduboy.print(F("1"));
    break;
  case 3:
    if (DEBUG_MODE_ENABLED) {
      currentMiniGame = DEBUG_MINIGAME;
    } else {
      currentMiniGame = (MiniGameState)random(NUM_GAMES);
    }
    intermissionTime = 0;
    gameState = STATE_GAMEPLAY;
    break;
  default:
    break;
  }
}

void doMainMenu() {
  arduboy.setCursor(40, 5);
  arduboy.print(F("MAIN MENU"));
  arduboy.drawFastHLine(0, 15, 128); // Separator

  // Handle menu navigation (UP/DOWN)
  if (arduboy.justPressed(UP_BUTTON)) {
    // Wrap around when moving up from the top option
    currentMenuOption =
        (MenuOption)((currentMenuOption - 1 + NUM_MENU_OPTIONS) %
                     NUM_MENU_OPTIONS);
  }
  if (arduboy.justPressed(DOWN_BUTTON)) {
    // Wrap around when moving down from the bottom option
    currentMenuOption =
        (MenuOption)((currentMenuOption + 1) % NUM_MENU_OPTIONS);
  }

  // Draw the menu options
  for (int i = 0; i < NUM_MENU_OPTIONS; i++) {
    arduboy.setCursor(45, 25 + (i * 10));

    // Indicate the currently selected option with an arrow
    if (i == currentMenuOption) {
      arduboy.print(">");
    } else {
      arduboy.print(" ");
    }

    switch (i) {
    case MENU_START_GAME:
      arduboy.print(F("START GAME"));
      break;
    case MENU_SETTINGS:
      arduboy.print(F("SETTINGS"));
      break;
    case MENU_QUIT:
      arduboy.print(F("QUIT"));
      break;
    }
  }

  // Handle selection (A/B button) and transition to the next state
  if (arduboy.justPressed(A_BUTTON | B_BUTTON)) {
    switch (currentMenuOption) {
    case MENU_START_GAME:
      gameState = STATE_GAMEPLAY;
      // Game specific setup (e.g., reset player position, score = 0)
      // resetGameVariables();
      if (DEBUG_MODE_ENABLED) {
        currentMiniGame = DEBUG_MINIGAME;
      } else {
        currentMiniGame = (MiniGameState)random(NUM_GAMES);
      }
      break;
    case MENU_SETTINGS:
      gameState = STATE_SETTINGS;
      break;
    case MENU_QUIT:
      gameState = STATE_GAME_OVER;
      break;
    }
  }
}

void doSettings() {
  arduboy.setCursor(40, 5);
  arduboy.print(F("SETTINGS"));
  arduboy.drawFastHLine(0, 15, 128);

  arduboy.setCursor(10, 30);
  arduboy.print(F("Volume: "));
  if (arduboy.audio.enabled()) {
    arduboy.print(F("ON"));
  } else {
    arduboy.print(F("OFF"));
  }

  arduboy.setCursor(10, 50);
  arduboy.print(F("A: Toggle  B: Return"));

  // Toggle logic
  if (arduboy.justPressed(A_BUTTON)) {
    if (arduboy.audio.enabled()) {
      arduboy.audio.off();
      arduboy.audio.saveOnOff();
    } else {
      arduboy.audio.on();
      arduboy.audio.saveOnOff();
    }
  }

  // Transition logic: Back to main menu
  if (arduboy.justPressed(B_BUTTON)) {
    gameState = STATE_MAIN_MENU;
  }
}

void doGameplay() {
  char scorefmt[] = "Score: %d";
  char scoreboard[20];
  snprintf(scoreboard, sizeof(scoreboard), scorefmt, score);
  // score board remains up for all games
  arduboy.setCursor(0, 0);
  arduboy.print(scoreboard);

  switch (currentMiniGame) {
  case GAME_ARROWS:
    doArrowsGame();
    break;
  case GAME_SIMON:
    doSimonGame();
    break;
  case GAME_SPOTLIGHT:
    doSpotlightGame();
    break;
  case GAME_MAKE_IT_HOT:
    doMakeItHotGame();
    break;
  case GAME_MARSHMALLOW_DROP:
    doMarshmallowDropGame();
    break;
  default:
    // Should never happen, but useful for debugging
    arduboy.print("ERROR STATE");
    break;
  }
}

void doGameOver() {
  arduboy.setCursor(35, 20);
  arduboy.print(F("G A M E   O V E R"));
  arduboy.setCursor(40, 40);
  arduboy.print(F("Final Score: 12345"));
  arduboy.setCursor(10, 50);
  arduboy.print(F("Press A to return to Menu"));

  // Transition logic: Back to main menu
  if (arduboy.justPressed(A_BUTTON)) {
    gameState = STATE_MAIN_MENU;
    // Reset the menu option selection on return
    currentMenuOption = MENU_START_GAME;
  }
}

void checkTransition() {
  // This function can be used to handle global transitions
  // like pausing the game from any state.
}
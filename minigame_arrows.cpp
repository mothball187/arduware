#include "minigame_arrows.h"

// Bring in the sprites we need from the main file for now, or declare them
// extern if they are in another header
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

unsigned int arrowsGame_lastSpawnTime = 0;
// number of arrows per game
uint8_t arrowsGame_numArrows = 10;
uint8_t arrowsGame_spawnTotal = 0;
bool arrowsGame_shouldSpawn = true;
int16_t arrowsGame_targetY = 48;
uint16_t arrowsGame_target = 6;
// x locations for the hit targets
int16_t arrowsGame_leftX = 5;
int16_t arrowsGame_rightX = 25;
int16_t arrowsGame_upX = 45;
int16_t arrowsGame_downX = 65;
int16_t arrowsGame_bX = 105;
int16_t arrowsGame_aX = 85;

// x,y x is which button it correspond to
int16_t arrowsGame_spawnPos[] = {-1, -1};
// x,y,frame (4 frames)
int16_t arrowsGame_bubblePos[] = {-1, -1, 0};
int16_t arrowsGame_XPos[] = {-1, -1, 0};

void arrowsGameAnimateSprites() {
  if (arrowsGame_bubblePos[0] >= 0) {
    if (arrowsGame_bubblePos[2] < 7) {
      Sprites::drawExternalMask(
          arrowsGame_bubblePos[0], arrowsGame_bubblePos[1], bubbleburst,
          bubbleburst_mask, arrowsGame_bubblePos[2], arrowsGame_bubblePos[2]);
      arrowsGame_bubblePos[2] += 1;
    } else {
      arrowsGame_bubblePos[0] = -1;
      arrowsGame_bubblePos[1] = -1;
      arrowsGame_bubblePos[2] = 0;
    }
  } else if (arrowsGame_XPos[0] >= 0) {
    if (arrowsGame_XPos[2] / 2 < 1) { // 2 == hold length
      Sprites::drawExternalMask(arrowsGame_XPos[0], arrowsGame_XPos[1], X, X,
                                arrowsGame_XPos[2] / 2, arrowsGame_XPos[2] / 2);
      arrowsGame_XPos[2] += 1;
    } else {
      arrowsGame_XPos[0] = -1;
      arrowsGame_XPos[1] = -1;
      arrowsGame_XPos[2] = 0;
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
  static const uint8_t *spawnBmp = left_arrow;
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
    arrowsGame_spawnPos[1] += 3;
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
      turnOnLED(COLOR_GREEN);
      arrowsGameHit();
    } else {
      turnOnLED(COLOR_RED);
      arrowsGameSpawnX();
      arrowsGameDespawn();
    }
  } else if (arduboy.justPressed(RIGHT_BUTTON)) {
    Sprites::drawExternalMask(arrowsGame_rightX, arrowsGame_targetY,
                              right_arrow, &right_arrow[2], 0, 0);
    if (arrowsGame_spawnPos[0] == arrowsGame_rightX &&
        abs(arrowsGame_spawnPos[1] - 3 - arrowsGame_targetY) <= 5) {
      turnOnLED(COLOR_GREEN);
      arrowsGameHit();
    } else {
      turnOnLED(COLOR_RED);
      arrowsGameSpawnX();
      arrowsGameDespawn();
    }
  } else if (arduboy.justPressed(UP_BUTTON)) {
    Sprites::drawExternalMask(arrowsGame_upX, arrowsGame_targetY, up_arrow,
                              &up_arrow[2], 0, 0);
    if (arrowsGame_spawnPos[0] == arrowsGame_upX &&
        abs(arrowsGame_spawnPos[1] - 3 - arrowsGame_targetY) <= 5) {
      turnOnLED(COLOR_GREEN);
      arrowsGameHit();
    } else {
      turnOnLED(COLOR_RED);
      arrowsGameSpawnX();
      arrowsGameDespawn();
    }
  } else if (arduboy.justPressed(DOWN_BUTTON)) {
    Sprites::drawExternalMask(arrowsGame_downX, arrowsGame_targetY, down_arrow,
                              &down_arrow[2], 0, 0);
    if (arrowsGame_spawnPos[0] == arrowsGame_downX &&
        abs(arrowsGame_spawnPos[1] - 3 - arrowsGame_targetY) <= 5) {
      turnOnLED(COLOR_GREEN);
      arrowsGameHit();
    } else {
      turnOnLED(COLOR_RED);
      arrowsGameSpawnX();
      arrowsGameDespawn();
    }
  } else if (arduboy.justPressed(B_BUTTON)) {
    Sprites::drawExternalMask(arrowsGame_bX, arrowsGame_targetY, button_filled,
                              &button_filled[2], 0, 0);
    if (arrowsGame_spawnPos[0] == arrowsGame_bX &&
        abs(arrowsGame_spawnPos[1] - 3 - arrowsGame_targetY) <= 5) {
      turnOnLED(COLOR_GREEN);
      arrowsGameHit();
    } else {
      turnOnLED(COLOR_RED);
      arrowsGameSpawnX();
      arrowsGameDespawn();
    }
  } else if (arduboy.justPressed(A_BUTTON)) {
    Sprites::drawExternalMask(arrowsGame_aX, arrowsGame_targetY, button_filled,
                              &button_filled[2], 0, 0);
    if (arrowsGame_spawnPos[0] == arrowsGame_aX &&
        abs(arrowsGame_spawnPos[1] - 3 - arrowsGame_targetY) <= 5) {
      turnOnLED(COLOR_GREEN);
      arrowsGameHit();
    } else {
      turnOnLED(COLOR_RED);
      arrowsGameSpawnX();
      arrowsGameDespawn();
    }
  }
  arrowsGameAnimateSprites();
}

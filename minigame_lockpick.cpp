#include "minigame_lockpick.h"
#include <math.h>

bool lockpick_newGame = true;
unsigned long lockpick_timer = 0;
unsigned long lockpick_lastScoreSecond =
    0;                       // Tracks the last whole second we deducted points
float lockpick_pinAngle = 0; // 0 = straight up, ranges roughly -PI/2 to PI/2
float lockpick_targetAngle = 0;
float lockpick_sweetSpotWidth = 0.3; // radians of leniency
float lockpick_cylinderAngle = 0;    // 0 = rest, PI/2 = fully turned
float lockpick_maxTurn = 0;          // max turn aloud at current pin angle

void doLockpickGame() {
  if (lockpick_newGame) {
    lockpick_timer = millis();
    lockpick_lastScoreSecond = 0;
    lockpick_pinAngle = 0;
    lockpick_cylinderAngle = 0;

    // Target is between -1.0 and 1.0 radians
    lockpick_targetAngle = (random(200) - 100) / 100.0;

    // Grant initial 100 points
    score += 100;

    lockpick_newGame = false;
  }

  // --- INPUT HANDLING ---

  // Left/Right adjust the pin IF the cylinder is at rest
  if (lockpick_cylinderAngle == 0) {
    if (arduboy.pressed(LEFT_BUTTON)) {
      lockpick_pinAngle -= 0.05;
    }
    if (arduboy.pressed(RIGHT_BUTTON)) {
      lockpick_pinAngle += 0.05;
    }
    // Clamp pin angle to top hemisphere (-PI/2 to PI/2)
    if (lockpick_pinAngle < -1.5)
      lockpick_pinAngle = -1.5;
    if (lockpick_pinAngle > 1.5)
      lockpick_pinAngle = 1.5;
  }

  // A applies tension
  if (arduboy.pressed(A_BUTTON)) {
    // Determine how far the cylinder can turn based on pin proximity to target
    float error = abs(lockpick_pinAngle - lockpick_targetAngle);
    if (error <= lockpick_sweetSpotWidth) {
      lockpick_maxTurn = PI / 2.0; // Full 90 degrees
    } else {
      // Map error to a max turn amount. The closer, the further it turns.
      // E.g., if error is 0.5, and max theoretical error is ~3.0
      lockpick_maxTurn = (PI / 2.0) * (1.0 - (error / 1.5));
      if (lockpick_maxTurn < 0.1)
        lockpick_maxTurn = 0.1; // always turns a tiny bit
    }

    // Turn cylinder
    lockpick_cylinderAngle += 0.05;
    if (lockpick_cylinderAngle > lockpick_maxTurn) {
      lockpick_cylinderAngle = lockpick_maxTurn;
      // Visual shake handled in drawing logic
    }
  } else {
    // Release tension, cylinder springs back
    lockpick_cylinderAngle -= 0.1;
    if (lockpick_cylinderAngle < 0) {
      lockpick_cylinderAngle = 0;
    }
  }

  // --- TIMER & SCORING ---

  unsigned long elapsed = millis() - lockpick_timer;
  unsigned long currentSeconds = elapsed / 1000;

  if (currentSeconds > lockpick_lastScoreSecond && currentSeconds < 10) {
    score = max(0, score - 10);
    turnOnLED(COLOR_RED, 250); // Flash red LED & play sound every second
    lockpick_lastScoreSecond = currentSeconds;
  }

  // --- WIN/LOSS CONDITIONS ---

  if (lockpick_cylinderAngle >= (PI / 2.0) - 0.01) {
    // Win!
    turnOnLED(COLOR_GREEN, 1000);
    lockpick_newGame = true;
    gameState = STATE_INTERMISSION;
    return;
  }

  if (elapsed >= 10000) {
    // Out of time
    turnOnLED(COLOR_RED, 1000);
    lockpick_newGame = true;
    gameState = STATE_INTERMISSION;
    return;
  }

  // --- DRAWING ---

  // Center of lock mechanism
  int cx = MAX_X_POS / 2;
  int cy = MAX_Y_POS / 2 + 10; // offset down a bit
  int radius = 20;

  // Draw Cylinder
  arduboy.drawCircle(cx, cy, radius, WHITE);
  arduboy.drawCircle(cx, cy, radius - 2, WHITE);

  // Calculate Keyhole rotation based on cylinder
  // Keyhole at rest is a vertical line. Cylinder turn goes clockwise.
  float keyholeAngle = lockpick_cylinderAngle;
  int kx1 = cx + sin(keyholeAngle) * (-10);
  int ky1 = cy - cos(keyholeAngle) * (-10);
  int kx2 = cx + sin(keyholeAngle) * (10);
  int ky2 = cy - cos(keyholeAngle) * (10);
  arduboy.drawLine(kx1, ky1, kx2, ky2, WHITE);

  // Calculate Bobby Pin rotation (moves with cylinder tension!)
  // Pin base is at center. Angle is user pin angle + cylinder turn angle.
  float currentPinAngle = lockpick_pinAngle + lockpick_cylinderAngle;

  // Add shake effect if tense and bound
  if (arduboy.pressed(A_BUTTON) &&
      abs(lockpick_cylinderAngle - lockpick_maxTurn) < 0.01 &&
      lockpick_maxTurn < (PI / 2.0) - 0.1) {
    // Alternate tiny shake based on frames
    if (arduboy.frameCount % 2 == 0) {
      currentPinAngle += 0.02;
    } else {
      currentPinAngle -= 0.02;
    }
  }

  int px = cx + sin(currentPinAngle) * 30; // Pointing upwards mostly
  int py = cy - cos(currentPinAngle) * 30;

  arduboy.drawLine(cx, cy - 4, px, py,
                   WHITE); // offset base slightly above keyhole
}

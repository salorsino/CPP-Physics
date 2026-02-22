#include "raylib.h"
#include <cmath>

const int screenWidth = 1000;
const int screenHeight = 500;
// start with an initial velocity
// define acceleration as force of gravity
// make acceleration same value as screenHeight to normalize it, make it feel
// real ball will be halfway down the screen at 1s (starting from the top) makes
// it modifiable as well
float acceleration = screenHeight;
// speed of the ball. increases based on accereration * time
float velocity = 0.0f;
float dt;
float dv;
Vector2 ballPositionV = {(float)screenWidth / 2, (float)screenHeight / 10};

/*
 * Draw FPS and velocity on screen
 */
void drawStats() {
  DrawFPS(10, 10);
  DrawText(TextFormat("Velocity: %f", velocity), 10, 75, 25, BLACK);
}

void drawBall(float ballPosition, float dv) {

  DrawCircleV(ballPositionV, 25, MAROON);
  // change in velocity is delta v (dv)
  // how much faster will the ball go after it has fallen dt?
  // add that to the current velocity
  dv = acceleration * dt;
  velocity += dv;

  // add the change in position to the current position of the ball
  ballPosition += velocity * dt;

  // ball hit the floor
  if (ballPosition > 475) {
    // keep it at the floor or it will sink through
    ballPosition = 475;
    // negate velocity so it bounces upward and take off some speed
    velocity = velocity * -0.8;
  }

  // if ball is on the floor and barely bouncing, set motion to zero
  if (std::abs(velocity) < 3.0 && ballPosition == 475) {
    velocity = 0;
    acceleration = 0;
  }
}

int main(void) {

  InitWindow(screenWidth, screenHeight, "raylib [core] example - input keys");

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    BeginDrawing();

    ClearBackground(RAYWHITE);
    drawStats();

    // get time since last frame. this is delta T
    dt = GetFrameTime();
    drawBall(ballPositionV.y, dv);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}

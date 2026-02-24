#include "raylib.h"
#include <cmath>
#include <vector>

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
Vector2 ballPosition = {(float)screenWidth / 2, (float)screenHeight / 10};

struct Ball {
  Vector2 position;
  float acceleration;
  float radius;
  float velocity;
};

/*
 * Draw FPS and velocity on screen
 */
void drawStats() {
  DrawFPS(10, 10);
}

void newDrawBall(std::vector<Ball> &balls) {
  for (Ball &ball : balls) {
    DrawCircleV(ball.position, 25, MAROON);
    // change in velocity is delta v (dv)
    // how much faster will the ball go after it has fallen dt, time for 1 frame
    // add that to the current velocity
    float dt = GetFrameTime();
    float dv = acceleration * dt;
    ball.velocity += dv;

    // add the change in position to the current position of the ball
    ball.position.y += ball.velocity * dt;

    // ball hit the floor
    if (ball.position.y > 475) {
      // keep it at the floor or it will sink through
      ball.position.y = 475;
      // negate velocity so it bounces upward and take off some speed
      ball.velocity = ball.velocity * -0.8;
    }

    // if ball is on the floor and barely bouncing, set motion to zero
    if (std::abs(ball.velocity) < 3.0 && ball.position.y == 475) {
      ball.velocity = 0;
      ball.acceleration = 0;
    }
  }
}

void drawBall() {

  DrawText(TextFormat("Position: %f", ballPosition.y), 10, 45, 25, BLACK);
  DrawCircleV(ballPosition, 25, MAROON);
  // change in velocity is delta v (dv)
  // how much faster will the ball go after it has fallen dt, time for 1 frame
  // add that to the current velocity
  float dt = GetFrameTime();
  float dv = acceleration * dt;
  velocity += dv;

  // add the change in position to the current position of the ball
  ballPosition.y += velocity * dt;

  // ball hit the floor
  if (ballPosition.y > 475) {
    // keep it at the floor or it will sink through
    ballPosition.y = 475;
    // negate velocity so it bounces upward and take off some speed
    velocity = velocity * -0.8;
  }

  // if ball is on the floor and barely bouncing, set motion to zero
  if (std::abs(velocity) < 3.0 && ballPosition.y == 475) {
    velocity = 0;
    acceleration = 0;
  }
}

int main(void) {

  InitWindow(screenWidth, screenHeight, "raylib [core] example - input keys");
  SetTargetFPS(60);

  Vector2 initialPosition = {(float)screenWidth / 2, (float)screenHeight / 10};
  Vector2 mousePosition;
  std::vector<Ball> balls = {};
  while (!WindowShouldClose()) {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
      mousePosition = GetMousePosition();
      Ball newBall = Ball();
      newBall.position = mousePosition;
      newBall.radius = 25;
      newBall.velocity = 0.0f;
      newBall.acceleration = acceleration;
      balls.push_back(newBall);
    }
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawFPS(10, 10);
    DrawText(TextFormat("Mouse Position - X: %f, Y: %f", mousePosition.x,
                        mousePosition.y),
             10, 50, 20, GOLD);
    newDrawBall(balls);
    EndDrawing();
  }

  CloseWindow();

  return 0;
}

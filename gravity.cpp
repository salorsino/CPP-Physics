#include "raylib.h"
#include <cmath>
#include <vector>

const int screenWidth = 1000;
const int screenHeight = 500;

struct Ball {
  Vector2 position;
  float acceleration;
  float radius;
  float velocity;
};

/*
 * Draw FPS and velocity on screen
 */
void drawStats() { DrawFPS(10, 10); }

// pass the vector of Balls in by reference so each ball remains independent and
// not related to global variables
void newDrawBall(std::vector<Ball> &balls) {
  for (Ball &ball : balls) {
    DrawCircleV(ball.position, 25, MAROON);
    // change in velocity is delta v (dv)
    // how much faster will the ball go after it has fallen dt, time for 1 frame
    // add that to the current velocity
    float dt = GetFrameTime();
    float dv = ball.acceleration * dt;
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

int main(void) {

  InitWindow(screenWidth, screenHeight, "raylib [core] example - input keys");
  SetTargetFPS(60);

  // Store where mouse was clicked and vector of Balls
  Vector2 mousePosition;
  std::vector<Ball> balls = {};
  while (!WindowShouldClose()) {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
      mousePosition = GetMousePosition();
      Ball newBall = Ball();
      newBall.position = mousePosition;
      newBall.radius = 25;
      newBall.velocity = 0.0f;
      /*
       * Acceleration is "gravity" in the simulator
       * By setting acceleration = screenHeight, and using d = 1/2*a*t^2
       * the ball will fall halfway down from the top in 1s. makes it feel real
       */
      newBall.acceleration = (float)screenHeight;
      balls.push_back(newBall);
    }
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawFPS(10, 10);
    newDrawBall(balls);
    EndDrawing();
  }

  CloseWindow();

  return 0;
}

#include "raylib.h"

#include <cmath>

typedef enum GameScreen { LOGO = 0, MAIN_MENU } GameScreen;

int main(void) {
  const int screenWidth = 960;
  const int screenHeight = 540;

  InitWindow(screenWidth, screenHeight, "Super Mario Bros.");
  Texture2D background_main = LoadTexture("assets/images/menu-2.png");
  Texture2D background_loading = LoadTexture("assets/images/Loading_menu.png");
  Texture2D mario = LoadTexture("assets/images/Mario.png");
  Texture2D cloud = LoadTexture("assets/images/Clouds.png");

  GameScreen currentScreen = LOGO;

  int framesCounter = 0;

  // Base positions
  float originalMarioX = 55, originalMarioY = 199;

  // Cloud 1 position and direction
  float cloud1X = 684, cloud1Y = 68;
  float cloud1Speed = 1.0f; // Speed of Cloud 1
  bool cloud1MovingRight = true;

  // Cloud 2 position and direction
  float cloud2X = 950, cloud2Y = 27; // Start on the left
  float cloud2Speed = 1.5f;          // Speed of Cloud 2
  bool cloud2MovingRight = true;

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    float time = (float)framesCounter / 60.0f;
    framesCounter++;

    switch (currentScreen) {
    case LOGO: {
      if (framesCounter > 180) {
        currentScreen = MAIN_MENU;
      }
    } break;

    case MAIN_MENU: {
      // Mario movement (up and down)
      originalMarioY = 199 + sin(time * 2.0f) * 20;

      // Cloud 1 movement
      if (cloud1MovingRight) {
        cloud1X += cloud1Speed;
        if (cloud1X + cloud.width >= screenWidth) {
          cloud1MovingRight = false;
        }
      } else {
        cloud1X -= cloud1Speed;
        if (cloud1X <= 640) {
          cloud1MovingRight = true;
        }
      }

      // Cloud 2 movement
      if (cloud2MovingRight) {
        cloud2X += cloud2Speed;
        if (cloud2X + cloud.width >= screenWidth) {
          cloud2MovingRight = false;
        }
      } else {
        cloud2X -= cloud2Speed;
        if (cloud2X <= 640) {
          cloud2MovingRight = true;
        }
      }
    } break;

    default:
      break;
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);

    switch (currentScreen) {
    case LOGO: {
      DrawTexture(background_loading, 0, 0, WHITE);
    } break;

    case MAIN_MENU: {
      DrawTexture(background_main, 0, 0, WHITE);
      DrawTexture(mario, originalMarioX, originalMarioY, WHITE);

      // Draw Cloud 1
      DrawTexture(cloud, cloud1X, cloud1Y, WHITE);
      // Draw Cloud 2
      DrawTexture(cloud, cloud2X, cloud2Y, WHITE);
    } break;

    default:
      break;
    }

    EndDrawing();
  }

  // Unload textures
  UnloadTexture(background_main);
  UnloadTexture(background_loading);
  UnloadTexture(mario);
  UnloadTexture(cloud);
  CloseWindow();
  return 0;
}

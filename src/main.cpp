/* 
#include "raylib.h"
#include <vector>
#include <string>
#include <cmath>

#define SCREEN_WIDTH 1500
#define SCREEN_HEIGHT 900
#define FLOOR_HEIGHT 500
#define GRAVITY 0.5f
#define MAX_FALL_SPEED 10.0f
#define JUMP_SPEED -10.0f
#define MAX_JUMP_TIME 12 // Maximum frames for holding the jump button

enum Direction { LEFT, RIGHT };
enum MotionState { STILL, WALK, AIRBORNE };

struct Player {
    float positionX;
    float positionY;
    float velocityX;
    float velocityY;
    float targetVelocityX;
    Direction heading;
    MotionState motionState;
    int animationFrame;
    int currentFrame;
    int animationTimer;
    int jumpTime; // Track the jump time
};

std::vector<Texture2D> marioFramesLeft;
std::vector<Texture2D> marioFramesRight;

void LoadSpriteGroup(std::vector<Texture2D>& spriteGroup, const std::vector<std::string>& spritePaths) {
    for (const auto& path : spritePaths) {
        Texture2D sprite = LoadTexture(path.c_str());
        spriteGroup.push_back(sprite);
    }
}

void UpdatePlayer(Player& player) {
    // Handle jump initiation
    if ((IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_UP)) && player.motionState != AIRBORNE) {
        player.velocityY = JUMP_SPEED;
        player.motionState = AIRBORNE;
        player.jumpTime = 0; // Reset jump time
    }

    // Handle holding the jump button to jump higher
    if ((IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_UP)) && player.motionState == AIRBORNE && player.jumpTime < MAX_JUMP_TIME) {
        player.velocityY = JUMP_SPEED; // Continue applying jump speed
        player.jumpTime++;
    }

    // Update vertical motion (gravity, jumping)
    if (player.motionState == AIRBORNE) {
        player.velocityY += GRAVITY;
        if (player.velocityY > MAX_FALL_SPEED) player.velocityY = MAX_FALL_SPEED;
        player.positionY += player.velocityY;

        if (player.positionY >= FLOOR_HEIGHT) { // Landing
            player.positionY = FLOOR_HEIGHT;
            player.motionState = STILL;
            player.velocityY = 0;
        }
    }

    // Update horizontal movement
    if (IsKeyDown(KEY_RIGHT)) {
        player.targetVelocityX = 4.5f;  // Move right
        player.heading = RIGHT;
        if (player.motionState != AIRBORNE) {
            player.motionState = WALK; // Set motion state to WALK
        }
    } else if (IsKeyDown(KEY_LEFT)) {
        player.targetVelocityX = -4.5f; // Move left
        player.heading = LEFT;
        if (player.motionState != AIRBORNE) {
            player.motionState = WALK; // Set motion state to WALK
        }
    } else {
        player.targetVelocityX = 0.0f;  // Stop moving
        if (player.motionState != AIRBORNE) {
            player.motionState = STILL; // Set motion state to STILL if no keys are pressed
        }
    }

    // Apply horizontal velocity
    if (player.velocityX < player.targetVelocityX) {
        player.velocityX += 0.5f; // Increase acceleration
    } else if (player.velocityX > player.targetVelocityX) {
        player.velocityX -= 0.5f; // Increase deceleration
    }

    // Add a small threshold to stop drifting
    if (fabs(player.velocityX) < 0.1f) {
        player.velocityX = 0.0f;
    }

    player.positionX += player.velocityX;

    // Bound player position to screen
    if (player.positionX < 0) player.positionX = 0;
    if (player.positionX > SCREEN_WIDTH - (marioFramesLeft[player.currentFrame].width) * 1.5f) 
        player.positionX = SCREEN_WIDTH - (marioFramesLeft[player.currentFrame].width  * 1.5f);
}

void UpdateAnimation(Player& player) {
    player.animationTimer--;
    if (player.animationTimer <= 0) {
        player.animationTimer = 12; // Reset animation timer
        if (player.motionState == WALK) {
            player.animationFrame = (player.animationFrame + 1) % 3; // Cycle through walking frames (1, 2, 3)
        } else player.animationFrame = (player.animationFrame + 1) % 2;
    }

    // Update sprite based on motion
    if (player.motionState == STILL) {
        player.currentFrame = 0; // Idle frame
    } else if (player.motionState == WALK) {
        player.currentFrame = 1 + player.animationFrame; // Walking frames (1, 2, 3)
    } else if (player.motionState == AIRBORNE) {
        player.currentFrame = 4; // Jumping frame
    }
}

void DrawPlayer(Player& player, float scale) {
    Vector2 position = { player.positionX, player.positionY };
    if (player.heading == LEFT) {
        DrawTextureEx(marioFramesLeft[player.currentFrame], position, 0.0f, scale, WHITE);
    } else {
        DrawTextureEx(marioFramesRight[player.currentFrame], position, 0.0f, scale, WHITE);
    }
} 

int main() {
    // Initialize raylib
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Mario Sprite Demo");

    // Set the window to full screen
    //ToggleFullscreen();

    // Load Mario sprite frames for left and right directions
    std::vector<std::string> spritePathsLeft = {
        "../mario_imgs/mario_left1.png",  // Idle frame
        "../mario_imgs/mario_left2.png",  // Walking frame 1
        "../mario_imgs/mario_left3.png",  // Walking frame 2
        "../mario_imgs/mario_left4.png",  // Walking frame 3
        "../mario_imgs/mario_left_jump.png" // Jumping frame
    };
    std::vector<std::string> spritePathsRight = {
        "../mario_imgs/mario_right1.png",  // Idle frame
        "../mario_imgs/mario_right2.png",  // Walking frame 1
        "../mario_imgs/mario_right3.png",  // Walking frame 2
        "../mario_imgs/mario_right4.png",  // Walking frame 3
        "../mario_imgs/mario_right_jump.png" // Jumping frame
    };
    LoadSpriteGroup(marioFramesLeft, spritePathsLeft);
    LoadSpriteGroup(marioFramesRight, spritePathsRight);

    Player player = { 100.0f, FLOOR_HEIGHT, 0.0f, 0.0f, 0.0f, RIGHT, STILL, 0, 0, 12, 0 };

    SetTargetFPS(60); // Set 60 FPS

    while (!WindowShouldClose()) {
        // Update player movement and animation
        UpdatePlayer(player);
        UpdateAnimation(player);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw player to the screen with a scale factor of 2.0 (double size)
        DrawPlayer(player, 2.0f);

        EndDrawing();
    }

    // Unload textures
    for (Texture2D texture : marioFramesLeft) {
        UnloadTexture(texture);
    }
    for (Texture2D texture : marioFramesRight) {
        UnloadTexture(texture);
    }

    CloseWindow(); // Close window and OpenGL context

    return 0;
}
*/

#include "raylib.h"
#define RAYLIB_TILESON_IMPLEMENTATION
#include "raylib-tileson.h"
#include <iostream>

int main() {
    const int screenWidth = 960;
    const int screenHeight = 540;
    InitWindow(screenWidth, screenHeight, "[raylib-tileson] example");
    SetTargetFPS(60);

    Map map = LoadTiled("../tilesets/map1.json");

    // Camera setup
    Camera2D camera = { 0 };
    camera.offset = { screenWidth / 2.0f, screenHeight / 2.0f };
    Vector2 position = { 0.0f, 0.0f };

    float mapHeight = 240.0f;
    float mapWidth = 2400.0f;
    camera.zoom = (float)screenHeight / mapHeight;

    while (!WindowShouldClose()) {
        if (IsKeyDown(KEY_RIGHT)) position.x += 5.0f;
        if (IsKeyDown(KEY_LEFT)) position.x -= 5.0f;
        
        if (position.x < screenWidth / 2.0f / camera.zoom) position.x = screenWidth / 2.0f / camera.zoom;
        if (position.x > mapWidth - screenWidth / 2.0f / camera.zoom) position.x = mapWidth - screenWidth / 2.0f / camera.zoom;
        // Ensure camera only moves horizontally
        camera.target = { position.x, mapHeight / 2.0f };

        BeginDrawing();
        ClearBackground(SKYBLUE);
        
        BeginMode2D(camera);
            DrawTiled(map, 0, 0, WHITE);
        EndMode2D();
        
        // Debug info
        DrawText(TextFormat("Position: %.0f, %.0f", position.x, position.y), 10, 10, 20, BLACK);
        DrawFPS(10, 50);
        
        EndDrawing();
    }

    UnloadMap(map);
    CloseWindow();
    return 0;
}
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <map>

#include "raylib/raylib-cpp.hpp"
#include "TileMap2D.h"

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 540
#define FLOOR_HEIGHT 192
#define GRAVITY 0.3f
#define MAX_FALL_SPEED 4.5
#define JUMP_SPEED -4.5
#define MAX_JUMP_TIME 10 // Maximum frames for holding the jump button
#define MAPHEIGHT 240.0
#define MAPWIDTH 2400.0
#define MAP_SCALE 1.0

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
    int spriteWidth; // Default sprite width
};

std::vector<Texture2D> marioFramesLeft;
std::vector<Texture2D> marioFramesRight;

void LoadSpriteGroup(std::vector<Texture2D>& spriteGroup, const std::vector<std::string>& spritePaths) {
    for (const auto& path : spritePaths) {
        Texture2D sprite = LoadTexture(path.c_str());
        spriteGroup.push_back(sprite);
    }
}

void ApplyHorizontalVelocity(Player& player) {
    if (player.velocityX < player.targetVelocityX) {
        player.velocityX += 0.2f; 
    } else if (player.velocityX > player.targetVelocityX) {
        player.velocityX -= 0.2f; 
    }

    if (std::fabs(player.velocityX) < 0.1f) {
        player.velocityX = 0.0f;
    }
}

void BoundPlayerPosition(Player& player) {
    if (player.positionX < 0) player.positionX = 0;
    if (player.positionX > MAPWIDTH - (marioFramesLeft[player.currentFrame].width) * 1.5f) 
        player.positionX = MAPWIDTH - (marioFramesLeft[player.currentFrame].width  * 1.5f);
}

void UpdateCamera(Camera2D& camera, Player& player) {
    const float cameraSpeed = 0.1f; 
    float targetCameraX = player.positionX;

    if (targetCameraX < SCREEN_WIDTH / 2.0f / camera.zoom) targetCameraX = SCREEN_WIDTH / 2.0f / camera.zoom;
    if (targetCameraX > MAPWIDTH - SCREEN_WIDTH / 2.0f / camera.zoom) targetCameraX = MAPWIDTH - SCREEN_WIDTH / 2.0f / camera.zoom;

    camera.target.x += (targetCameraX - camera.target.x) * cameraSpeed;
    camera.target.y = MAPHEIGHT / 2.0f;
}

void UpdatePlayerAndCamera(Player& player, Camera2D& camera, TileMap2D& map) {
    if ((IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_UP)) && player.motionState != AIRBORNE) {
        player.velocityY = JUMP_SPEED;
        player.motionState = AIRBORNE;
        player.jumpTime = 0;
    }

    if ((IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_UP)) && player.motionState == AIRBORNE && player.jumpTime < MAX_JUMP_TIME) {
        player.velocityY = JUMP_SPEED;
        player.jumpTime++;
    }

    if (player.motionState == AIRBORNE) {
        player.velocityY += GRAVITY;
        if (player.velocityY > MAX_FALL_SPEED) player.velocityY = MAX_FALL_SPEED;
        player.positionY += player.velocityY;

        if (player.positionY >= FLOOR_HEIGHT) {
            player.positionY = FLOOR_HEIGHT;
            player.motionState = STILL;
            player.velocityY = 0;
        }
    }

    if (IsKeyDown(KEY_RIGHT)) {
        player.targetVelocityX = 1.5f;
        player.heading = RIGHT;
        if (player.motionState != AIRBORNE) {
            player.motionState = WALK;
        }
    } else if (IsKeyDown(KEY_LEFT)) {
        player.targetVelocityX = -1.5f;
        player.heading = LEFT;
        if (player.motionState != AIRBORNE) {
            player.motionState = WALK;
        }
    } else {
        player.targetVelocityX = 0.0f;
        if (player.motionState != AIRBORNE) {
            player.motionState = STILL;
        }
    }

    ApplyHorizontalVelocity(player);
    player.positionX += player.velocityX;
    BoundPlayerPosition(player);
    UpdateCamera(camera, player);
}

void UpdateAnimation(Player& player) {
    player.animationTimer--;
    if (player.animationTimer <= 0) {
        player.animationTimer = 12;
        if (player.motionState == WALK) {
            player.animationFrame = (player.animationFrame + 1) % 3;
        } else player.animationFrame = (player.animationFrame + 1) % 2;
    }

    if (player.motionState == STILL) {
        player.currentFrame = 0;
    } else if (player.motionState == WALK) {
        player.currentFrame = 1 + player.animationFrame;
    } else if (player.motionState == AIRBORNE) {
        player.currentFrame = 4;
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
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Mario Sprite Demo");

    std::vector<std::string> spritePathsLeft = {
        "../mario_imgs/mario_left1.png",
        "../mario_imgs/mario_left2.png",
        "../mario_imgs/mario_left3.png",
        "../mario_imgs/mario_left4.png",
        "../mario_imgs/mario_left_jump1.png"
    };
    std::vector<std::string> spritePathsRight = {
        "../mario_imgs/mario_right1.png",
        "../mario_imgs/mario_right2.png",
        "../mario_imgs/mario_right3.png",
        "../mario_imgs/mario_right4.png",
        "../mario_imgs/mario_right_jump1.png"
    };
    LoadSpriteGroup(marioFramesLeft, spritePathsLeft);
    LoadSpriteGroup(marioFramesRight, spritePathsRight);

    //std::unique_ptr<tson::Map> map = loadTileMap("../Tiled/map1.json");
    std::string mapFilePath = "../Tiled/map1.json";
    TileMap2D tileMap(mapFilePath);
    Camera2D camera = { 0 };
    camera.offset = { SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f };
    Vector2 position = { 0.0f, 0.0f };
    
    camera.zoom = (float)SCREEN_HEIGHT / MAPHEIGHT;

    Player player = { 0.0f, FLOOR_HEIGHT, 0.0f, 0.0f, 0.0f, RIGHT, STILL, 0, 0, 12, 0, 16 };
    camera.target = { player.positionX, player.positionY };

    //Physics world setup (if required for collision)
    b2Vec2 gravity(0.0f, -9.8f);  // Set gravity for the physics world
    b2World physicsWorld(gravity);
    tileMap.generatePhysicsObjects(physicsWorld, MAP_SCALE);

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        UpdatePlayerAndCamera(player, camera, tileMap);
        UpdateAnimation(player);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode2D(camera);
            //DrawTiled(*map, 0, 0, WHITE);
        tileMap.draw(camera, MAP_SCALE);              // Draw the tile map
        tileMap.drawGrid(camera, MAP_SCALE);          // Draw grid (optional)
        tileMap.drawCollisionShapes(camera, MAP_SCALE); // Draw collision shapes (optional)
            DrawPlayer(player, 0.5f);
        EndMode2D();

        DrawText(TextFormat("Position: %.0f, %.0f", player.positionX, player.positionY), 10, 10, 20, BLACK);
        DrawFPS(10, 50);

        EndDrawing();
    }

    for (Texture2D texture : marioFramesLeft) {
        UnloadTexture(texture);
    }
    for (Texture2D texture : marioFramesRight) {
        UnloadTexture(texture);
    }

    CloseWindow();

    return 0;
}
      

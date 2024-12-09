#include "raylib.h"
#define RAYLIB_TILESON_IMPLEMENTATION

#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <map>
#include "raylib-tileson.h"
#include "tileson.hpp"

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 540
#define FLOOR_HEIGHT 192
#define GRAVITY 0.3f
#define MAX_FALL_SPEED 4.5
#define JUMP_SPEED -4.5
#define MAX_JUMP_TIME 10 // Maximum frames for holding the jump button
#define MAPHEIGHT 240.0
#define MAPWIDTH 2400.0

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

// Map LoadMap(const char* mapFilePath) {
//     return LoadTiled(mapFilePath);
// }

// Check for landing on the floor or objects
bool CheckLanding(Player& player, Map& map) {
    bool landed = false;
    RaylibTilesonData* data = (RaylibTilesonData*)map.data;
    if (data == NULL) {
        TraceLog(LOG_WARNING, "TILESON: Cannot draw empty map");
        return landed;
    }
    tson::Map* tsonMap = data->map;
    auto &layers = tsonMap->getLayers();
    for (const auto& layer : layers) {
        if (layer.getType() == tson::LayerType::ObjectGroup) {
            auto objectLayer = layer;
            for (const auto& object : objectLayer.getObjects()) {
                if (player.positionX < object.getPosition().x + object.getSize().x &&
                    player.positionX + player.spriteWidth > object.getPosition().x &&
                    player.positionY + player.spriteWidth > object.getPosition().y &&
                    player.positionY < object.getPosition().y + object.getSize().y) {
                    player.positionY = object.getPosition().y; // Điều chỉnh theo đối tượng
                    player.motionState = STILL;
                    player.velocityY = 0;
                    landed = true;
                    break;
                }
            }
        }
    }
    return landed;
}

// Apply smooth acceleration and deceleration for horizontal movement
void ApplyHorizontalVelocity(Player& player) {
    if (player.velocityX < player.targetVelocityX) {
        player.velocityX += 0.2f; 
    } else if (player.velocityX > player.targetVelocityX) {
        player.velocityX -= 0.2f; 
    }

    if (fabs(player.velocityX) < 0.1f) {
        player.velocityX = 0.0f;
    }
}

// Bound player position within the screen
void BoundPlayerPosition(Player& player) {
    if (player.positionX < 0) player.positionX = 0;
    if (player.positionX > MAPWIDTH - (marioFramesLeft[player.currentFrame].width) * 1.5f) 
        player.positionX = MAPWIDTH - (marioFramesLeft[player.currentFrame].width  * 1.5f);
}

// Update the camera based on player's position and velocity
void UpdateCamera(Camera2D& camera, Player& player) {
   
    const float cameraSpeed = 0.1f; 
    float targetCameraX = player.positionX;

    // Bound the camera horizontally to the map boundaries
    if (targetCameraX < SCREEN_WIDTH / 2.0f / camera.zoom) targetCameraX = SCREEN_WIDTH / 2.0f / camera.zoom;
    if (targetCameraX > MAPWIDTH - SCREEN_WIDTH / 2.0f / camera.zoom) targetCameraX = MAPWIDTH - SCREEN_WIDTH / 2.0f / camera.zoom;

    
    camera.target.x += (targetCameraX - camera.target.x) * cameraSpeed;

    // Keep the camera's vertical position centered
    camera.target.y = MAPHEIGHT / 2.0f;
}

void UpdatePlayerAndCamera(Player& player, Camera2D& camera, Map& map) {
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

        // Check if player lands on floor or objects
        //bool landed = CheckLanding(player, map);
        if (player.positionY >= FLOOR_HEIGHT) { // Default ground level fallback
            player.positionY = FLOOR_HEIGHT;
            player.motionState = STILL;
            player.velocityY = 0;
        }
    }

    // Update horizontal movement
    if (IsKeyDown(KEY_RIGHT)) {
        player.targetVelocityX = 1.5f;  // Move right
        player.heading = RIGHT;
        if (player.motionState != AIRBORNE) {
            player.motionState = WALK; // Set motion state to WALK
        }
    } else if (IsKeyDown(KEY_LEFT)) {
        player.targetVelocityX = -1.5f; // Move left
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

    // Apply horizontal velocity with smooth acceleration/deceleration
    ApplyHorizontalVelocity(player);

    // Update the player's position
    player.positionX += player.velocityX;

    // Bound player position to screen
    BoundPlayerPosition(player);

    // Update Camera movement (combined with player velocity)
    UpdateCamera(camera, player);
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

    // Load Mario sprite frames for left and right directions
    std::vector<std::string> spritePathsLeft = {
        "../mario_imgs/mario_left1.png",  // Idle frame
        "../mario_imgs/mario_left2.png",  // Walking frame 1
        "../mario_imgs/mario_left3.png",  // Walking frame 2
        "../mario_imgs/mario_left4.png",  // Walking frame 3
        "../mario_imgs/mario_left_jump1.png" // Jumping frame
    };
    std::vector<std::string> spritePathsRight = {
        "../mario_imgs/mario_right1.png",  // Idle frame
        "../mario_imgs/mario_right2.png",  // Walking frame 1
        "../mario_imgs/mario_right3.png",  // Walking frame 2
        "../mario_imgs/mario_right4.png",  // Walking frame 3
        "../mario_imgs/mario_right_jump1.png" // Jumping frame
    };
    LoadSpriteGroup(marioFramesLeft, spritePathsLeft);
    LoadSpriteGroup(marioFramesRight, spritePathsRight);

    // Load map
    Map map = LoadTiled("../tilesets/map1.json");

    // Camera setup
    Camera2D camera = { 0 };
    camera.offset = { SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f };
    Vector2 position = { 0.0f, 0.0f };
    
    camera.zoom = (float)SCREEN_HEIGHT / MAPHEIGHT;

    Player player = { 0.0f, FLOOR_HEIGHT, 0.0f, 0.0f, 0.0f, RIGHT, STILL, 0, 0, 12, 0, 16 };
    camera.target = { player.positionX, player.positionY };
    SetTargetFPS(60); // Set 60 FPS

    while (!WindowShouldClose()) {
        // Handle player input and movement
        UpdatePlayerAndCamera(player, camera, map);
        
        UpdateAnimation(player);

        // Begin drawing
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw the map and player
        BeginMode2D(camera);
            DrawTiled(map, 0, 0, WHITE);
            DrawPlayer(player, 0.5f);
        EndMode2D();

        // Debug info./
        DrawText(TextFormat("Position: %.0f, %.0f", player.positionX, player.positionY), 10, 10, 20, BLACK);
        DrawFPS(10, 50);

        EndDrawing();
    }

    // Unload textures and map
    for (Texture2D texture : marioFramesLeft) {
        UnloadTexture(texture);
    }
    for (Texture2D texture : marioFramesRight) {
        UnloadTexture(texture);
    }
    UnloadMap(map);

    CloseWindow(); // Close window and OpenGL context

    return 0;
}

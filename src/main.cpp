#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <map>

#include "raylib-cpp.hpp"
#include "map/TileMap2D.h"
#include "actor/MarioCharacter.h"
#include "Collision/CollisionManager.h"
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

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Mario Sprite Demo");

    std::vector<std::string> spritePathsLeft = {
        "../assets/images/mario_imgs/mario_left1.png",
        "../assets/images/mario_imgs/mario_left2.png",
        "../assets/images/mario_imgs/mario_left3.png",
        "../assets/images/mario_imgs/mario_left4.png",
        "../assets/images/mario_imgs/mario_left_jump1.png"
    };
    std::vector<std::string> spritePathsRight = {
        "../assets/images/mario_imgs/mario_right1.png",
        "../assets/images/mario_imgs/mario_right2.png",
        "../assets/images/mario_imgs/mario_right3.png",
        "../assets/images/mario_imgs/mario_right4.png",
        "../assets/images/mario_imgs/mario_right_jump1.png"
    };
    std::string mapFilePath = "../assets/maps/Tiled/map1.json";
    TileMap2D tileMap(mapFilePath);
    Camera2D camera = { 0 };
    
    camera.zoom = (float)SCREEN_HEIGHT / MAPHEIGHT;

    MarioCharacter player(spritePathsLeft, spritePathsRight);
    camera.target = { 0.0f, 0.0f };
    camera.offset = { SCREEN_WIDTH/2.0f, SCREEN_HEIGHT/2.0f };

    player.setPosition(20.0f, FLOOR_HEIGHT);  // Starting position

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
    // Update
    player.UpdatePlayerAndCamera(camera, tileMap);
    CollisionManager::HandlePlayerMapCollision(player, tileMap);
    player.UpdateAnimation();

    BeginDrawing();
    ClearBackground(RAYWHITE);

    BeginMode2D(camera);
        // Draw map
        tileMap.draw(camera, MAP_SCALE);
        player.draw(0.5f);
        
        // Debug drawing
        // Draw player collision box
        Rectangle playerRect = {
            player.getPositionX(),
            player.getPositionY(),
            player.getWidth(),
            player.getHeight()
        };
        DrawRectangleLinesEx(playerRect, 2.0f, RED);

        auto solidTiles = tileMap.getSolidTiles();
        for (const auto& tile : solidTiles) {
            DrawRectangleLinesEx(tile, 2.0f, GREEN);
            // Print coordinates for debugging
            DrawText(TextFormat("X:%.0f Y:%.0f", tile.x, tile.y), 
                    tile.x, tile.y, 10, RED);
        }

        // Draw collision info
        DrawText(TextFormat("Player Pos: %.2f, %.2f", 
            player.getPositionX(), player.getPositionY()), 
            10, 70, 20, RED);
        DrawText(TextFormat("On Ground: %s", 
            player.isOnGround ? "Yes" : "No"),
            10, 90, 20, RED);
    EndMode2D();

    DrawFPS(10, 50);
    EndDrawing();
}
    CloseWindow();

    return 0;
}
      
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <map>

#include "raylib-cpp.hpp"
#include "map/TileMap2D.h"
#include "actor/MarioCharacter.h"

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
    camera.offset = { SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f };
    Vector2 position = { 0.0f, 0.0f };
    
    camera.zoom = (float)SCREEN_HEIGHT / MAPHEIGHT;

    MarioCharacter player(spritePathsLeft, spritePathsRight);
    camera.target = { player.positionX, player.positionY };

    //Physics world setup (if required for collision)
    b2Vec2 gravity(0.0f, -9.8f);  // Set gravity for the physics world
    b2World physicsWorld(gravity);
    tileMap.generatePhysicsObjects(physicsWorld, MAP_SCALE);

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        player.UpdatePlayerAndCamera(camera, tileMap);
        player.UpdateAnimation();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode2D(camera);
        tileMap.draw(camera, MAP_SCALE);              // Draw the tile map
        //tileMap.drawGrid(camera, MAP_SCALE);          // Draw grid (optional)
        //tileMap.drawCollisionShapes(camera, MAP_SCALE); // Draw collision shapes (optional)
            player.draw(0.5f);
        EndMode2D();

        DrawText(TextFormat("Position: %.0f, %.0f", player.positionX, player.positionY), 10, 10, 20, BLACK);
        DrawFPS(10, 50);

        EndDrawing();
    }
    CloseWindow();

    return 0;
}
      

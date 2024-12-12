#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <map>

#include "raylib/raylib-cpp.hpp"
#include "TileMap2D.h"
#include "CharacterActor.h"

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 540
#define GRAVITY 0.3f
#define MAX_FALL_SPEED 4.5
#define JUMP_SPEED -4.5
#define MAX_JUMP_TIME 10 // Maximum frames for holding the jump button
#define MAPHEIGHT 240.0
#define MAPWIDTH 2400.0
#define MAP_SCALE 1.0

enum Direction { LEFT, RIGHT };
enum MotionState { STILL, WALK, AIRBORNE };

void UpdateCamera(Camera2D& camera, CharacterActor& player) {
    const float cameraSpeed = 0.1f;
    float targetCameraX = player.getPositionX();

    if (targetCameraX < SCREEN_WIDTH / 2.0f / camera.zoom) targetCameraX = SCREEN_WIDTH / 2.0f / camera.zoom;
    if (targetCameraX > MAPWIDTH - SCREEN_WIDTH / 2.0f / camera.zoom) targetCameraX = MAPWIDTH - SCREEN_WIDTH / 2.0f / camera.zoom;

    camera.target.x += (targetCameraX - camera.target.x) * cameraSpeed;
    camera.target.y = MAPHEIGHT / 2.0f;
}

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Mario Sprite Demo");

    std::string mapFilePath = "../Tiled/map1.json";
    TileMap2D tileMap(mapFilePath);
    Camera2D camera = { 0 };
    camera.offset = { SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f };
    camera.target = { 0, 0 };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    CharacterActor player;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        player.update();
        UpdateCamera(camera, player);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode2D(camera);
        tileMap.draw(MAP_SCALE);
        player.draw(MAP_SCALE);
        EndMode2D();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

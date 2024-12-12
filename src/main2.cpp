#include "raylib.h"
#include "CharacterActor.h"
#include "InputHandler.h"
#include "TileMap2D.h"
#include <box2d/box2d.h>
#include <memory>

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 540
#define GRAVITY 0.3f
#define MAPHEIGHT 240.0
#define MAPWIDTH 2400.0
#define MAP_SCALE 1.0
#define GROUND_HEIGHT 192.0f

void UpdateCamera(Camera2D& camera, CharacterActor& player) {
    const float cameraSpeed = 0.1f;
    float targetCameraX = player.getPositionX();

    if (targetCameraX < SCREEN_WIDTH / 2.0f / camera.zoom) targetCameraX = SCREEN_WIDTH / 2.0f / camera.zoom;
    if (targetCameraX > MAPWIDTH - SCREEN_WIDTH / 2.0f / camera.zoom) targetCameraX = MAPWIDTH - SCREEN_WIDTH / 2.0f / camera.zoom;

    camera.target.x += (targetCameraX - camera.target.x) * cameraSpeed;
    camera.target.y = MAPHEIGHT / 2.0f;
}

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Character Actor Test");

    std::string mapFilePath = "../Tiled/map1.json";
    TileMap2D tileMap(mapFilePath);

    Camera2D camera = { 0 };
    camera.offset = { SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f };
    camera.zoom = (float)SCREEN_HEIGHT / MAPHEIGHT;

    // Physics world setup
    b2Vec2 gravity(0.0f, -9.8f);  // Gravity for the physics world
    b2World physicsWorld(gravity);
    tileMap.generatePhysicsObjects(physicsWorld, MAP_SCALE);

    // Create and initialize the CharacterActor
    CharacterActor character(0.5f);
    float initialX = 5.0f; // Initial horizontal position of the character
    float initialY = GROUND_HEIGHT; // Character starts at ground height
    character.setInitialPosition(physicsWorld, MAP_SCALE, initialX, initialY);

    // Input handler
    InputHandler inputHandler;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // Update character based on input
        character.updateFromInput(inputHandler);
        character.updateAnimation();

        // Update physics world
        physicsWorld.Step(1.0f / 60.0f, 6, 2);

        // Update camera position
        UpdateCamera(camera, character);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode2D(camera);
        tileMap.draw(camera, MAP_SCALE);              // Draw the tile map
        tileMap.drawGrid(camera, MAP_SCALE);          // Draw grid (optional)
        tileMap.drawCollisionShapes(camera, MAP_SCALE); // Draw collision shapes (optional)
        character.draw(1.0);                   // Draw the character
        EndMode2D();

        DrawText(TextFormat("Position: %.2f, %.2f", character.getPositionX(), character.getPositionY()), 10, 10, 20, BLACK);
        DrawFPS(10, 50);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}

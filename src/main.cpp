// #include "raylib.h"
// #define RAYLIB_TILESON_IMPLEMENTATION
// #include "raylib-tileson.h"
// #include <iostream>

// int main() {
//     const int screenWidth = 960;
//     const int screenHeight = 540;
//     const int mapWidth = 2400; // 16 * 150 = 
//     InitWindow(screenWidth, screenHeight, "[raylib-tileson] example");
//     SetTargetFPS(60);

//     Map map = LoadTiled("../assets/maps/tilesets/map1.json");

//     // Camera setup
//     Camera2D camera = { 0 };
//     camera.offset = { screenWidth / 2.0f, screenHeight / 2.0f };
//     Vector2 position = { 0.0f, 0.0f };

//     float mapHeight = 240.0f;
//     camera.zoom = (float)screenHeight / mapHeight;

//     while (!WindowShouldClose()) {
//         if (IsKeyDown(KEY_RIGHT)) position.x += 10.0f;
//         if (IsKeyDown(KEY_LEFT)) position.x -= 10.0f;

//         if (position.x < screenWidth / 2.0f / camera.zoom) position.x = screenWidth / 2.0f / camera.zoom;
//         if (position.x > mapWidth - screenWidth / 2.0f / camera.zoom) position.x = mapWidth - screenWidth / 2.0f / camera.zoom;
//         // Ensure camera only moves horizontally
//         camera.target = { position.x, mapHeight / 2.0f };

//         BeginDrawing();
//         ClearBackground(SKYBLUE);
        
//         BeginMode2D(camera);
//             DrawTiled(map, 0, 0, WHITE);
//         EndMode2D();
        
//         // Debug info
//         DrawText(TextFormat("Position: %.0f, %.0f", position.x, position.y), 10, 10, 20, BLACK);
//         DrawFPS(10, 50);
        
//         EndDrawing();
//     }

//     UnloadMap(map);
//     CloseWindow();
//     return 0;
// }

#include "raylib.h"
#include <box2d/box2d.h>
#include "game/Game.h"
#include <iostream>

int main(void) {
    Game::Run();
    return 0;
}
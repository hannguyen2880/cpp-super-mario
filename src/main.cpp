#include "game/Game.h"
#include "game/GameManager.h"
#include "Constants.h"

int main() {
    //Game::Run();
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Mario Maker");

    InitAudioDevice();

    SetTargetFPS(60);
    const char* mapFilepath_ = "../assets/maps/map_1.tmx";

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        GameManager game(mapFilepath_, SCREEN_WIDTH, SCREEN_HEIGHT, SECOND_PLAYER);
        game.mainLoop();
        EndDrawing();
    }
    return 0;
}
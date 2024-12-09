#include "raylib.h"

#include "game/Game.h"
#include "screens/Screen.h"

int main(void) {
    InitWindow(960, 540, "Super Mario Bros.");
    InitAudioDevice();
    SetTargetFPS(60);
    Game::Init();
    int screenWidth, screenHeight;
    while (!WindowShouldClose()) {
        Game::Update();
        Game::Draw();
    }
    Game::Unload();
    CloseAudioDevice();
    CloseWindow();
    return 0;
}
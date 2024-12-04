#include "raylib.h"
#include <box2d/box2d.h>
#include <nlohmann/json.hpp>
#include <GLFW/glfw3.h>
#include "game/Game.h"
#include <iostream>
#include "tinyxml2.h"

int main(void) {
    InitWindow(960, 540, "Super Mario Bros.");
    InitAudioDevice();
    SetTargetFPS(60);
    Game::Init();
    
    while (!WindowShouldClose()) {
        Game::Update();
        Game::Draw();
    }
    
    Game::Unload();
    CloseAudioDevice();
    CloseWindow();
    return 0;
}
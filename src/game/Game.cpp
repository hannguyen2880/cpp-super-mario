#include "Game.h"
#include "../screens/MenuScreen.h"
#include <iostream>

GameState Game::currentState = GameState::MAIN_MENU;
std::unique_ptr<Screen> Game::currentScreen = nullptr;
Music Game::backgroundMusic = { 0 };

void Game::Init() {
    backgroundMusic = LoadMusicStream("assets/sounds/background-sound.mp3");
    SetMusicVolume(backgroundMusic, 1.0f);
    PlayMusicStream(backgroundMusic);

    // Set to loop automatically
    backgroundMusic.looping = true;
    currentScreen = std::make_unique<MenuScreen>();
    currentScreen->Init();
}

void Game::Update() {
    UpdateMusicStream(backgroundMusic);

    if (currentScreen) {
        currentScreen->Update();
    }
}
void Game::Unload() {
    UnloadMusicStream(backgroundMusic);
    //UnloadSound(jumpSound);
    //UnloadSound(coinSound);
}

void Game::Draw() {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    
    if (currentScreen) {
        currentScreen->Draw();
    }
    
    EndDrawing();
}

void Game::SetState(GameState newState) {
    currentState = newState;
    // Handle state change logic here
}
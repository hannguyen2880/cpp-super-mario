#include "Game.h"
#include "../screens/MenuScreen.h"
#include "../screens/InstructionScreen.h"
#include "../screens/BeforeGameScreen.h"
#include "../screens/GamePlayScreen.h"
#include <iostream>

GameState Game::currentState = GameState::MAIN_MENU;
std::unique_ptr<Screen> Game::currentScreen = nullptr;
// GameDifficulty Game::difficulty = GameDifficulty::MEDIUM;
// GameplayMode Game::gameplayMode = GameplayMode::MULTI_PLAYER;
// Character Game::character = Character::MARIO;

void Game::Init() {
    currentScreen = std::make_unique<MenuScreen>();
    currentScreen->Init();
}

void Game::Run() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Super Mario Bros.");
    InitAudioDevice();
    SetTargetFPS(60);
    Init();
    
    while (!WindowShouldClose()) {
        Update();
        Draw();
    }
    
    Unload();
    CloseAudioDevice();
    CloseWindow();
}

void Game::Update() {
    if (currentScreen) {
        currentScreen->Update();
    }
}
void Game::Unload() {
    //AudioManager::GetInstance().UnloadAllSounds();
   // AudioManager::GetInstance().UnloadAllMusics();
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
    
    if (currentScreen) {
        currentScreen->Unload();
        currentScreen = nullptr;
    }
    
    switch (newState) {
        case GameState::MAIN_MENU: {
            currentScreen = std::make_unique<MenuScreen>();
            break;
        }
        case GameState::INSTRUCTIONS: {
            currentScreen = std::make_unique<InstructionScreen>();
            break;
        }
        case GameState::SCOREBOARD: {
            currentScreen = std::make_unique<InstructionScreen>();
            break;
        }
        case GameState::BEFOREGAME: {
            currentScreen = std::make_unique<BeforeGameScreen>();
            break;
        }
        case GameState::GAMEPLAY: {
            currentScreen = std::make_unique<GameplayScreen>();
            break;
        }
    }
    
    if (currentScreen) {
        currentScreen->Init();
    }
}
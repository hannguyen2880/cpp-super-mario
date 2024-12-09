#include "Game.h"
#include "../screens/MenuScreen.h"
#include "../screens/InstructionScreen.h"
#include "../screens/BeforeGameScreen.h"
#include "../screens/GamePlayScreen.h"
#include <iostream>

GameState Game::currentState = GameState::MAIN_MENU;
std::unique_ptr<Screen> Game::currentScreen = nullptr;
Music Game::backgroundMusic = { 0 };
GameDifficulty Game::difficulty = GameDifficulty::MEDIUM;
GameplayMode Game::gameplayMode = GameplayMode::NEW_GAME;

void Game::Init() {
    backgroundMusic = LoadMusicStream("../assets/sounds/background_sound.mp3");
    SetMusicVolume(backgroundMusic, 1.0f);
    PlayMusicStream(backgroundMusic);
    backgroundMusic.looping = true;

    currentScreen = std::make_unique<MenuScreen>();
    currentScreen->Init();
}

void Game::Run() {
    InitWindow(960, 540, "Super Mario Bros.");
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
    UpdateMusicStream(backgroundMusic);
    // Debug print current music time
    float currentTime = GetMusicTimePlayed(backgroundMusic);
    float totalTime = GetMusicTimeLength(backgroundMusic);
    if (currentTime >= totalTime - 0.1f) {
        // Reset music if near end
        StopMusicStream(backgroundMusic);
        PlayMusicStream(backgroundMusic);
    }

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
        case GameState::BEFOREGAME: {
            currentScreen = std::make_unique<BeforeGameScreen>();
            break;
        }
    }
    
    if (currentScreen) {
        currentScreen->Init();
    }
}

void Game::SetDifficulty(GameDifficulty diff) {
    difficulty = diff;
}
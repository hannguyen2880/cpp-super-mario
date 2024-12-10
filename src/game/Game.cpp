#include "Game.h"
#include "../screens/MenuScreen.h"
#include "../screens/InstructionScreen.h"
#include "../screens/BeforeGameScreen.h"
#include "../screens/GamePlayScreen.h"
#include <iostream>

GameState Game::currentState = GameState::MAIN_MENU;
std::unique_ptr<Screen> Game::currentScreen = nullptr;
GameDifficulty Game::difficulty = GameDifficulty::MEDIUM;
GameplayMode Game::gameplayMode = GameplayMode::NEW_GAME;

void Game::Init() {
    InitAudioDevice(); 

    AudioManager::GetInstance().LoadMusics("background", "../assets/sounds/background_sound.mp3");
    AudioManager::GetInstance().PlayMusics("background");

    // Load sounds using AudioManager
    //AudioManager::GetInstance().LoadSounds("jump", "../assets/sounds/jump.wav");
    //AudioManager::GetInstance().LoadSounds("coin", "../assets/sounds/coin.wav");

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
    UpdateMusicStream(AudioManager::GetInstance().GetMusic("background"));
    float currentTime = GetMusicTimePlayed(AudioManager::GetInstance().GetMusic("background"));
    float totalTime = GetMusicTimeLength(AudioManager::GetInstance().GetMusic("background"));
    if (currentTime >= totalTime - 0.1f) {
        // Reset music if near end
        AudioManager::GetInstance().StopMusics("background");
        AudioManager::GetInstance().PlayMusics("background");
    }

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
#include "Game.h"
#include "../screens/MenuScreen.h"
#include "../screens/InstructionScreen.h"
#include "../screens/BeforeGameScreen.h"
#include <iostream>

GameState Game::currentState = GameState::MAIN_MENU;
std::unique_ptr<Screen> Game::currentScreen = nullptr;
Music Game::backgroundMusic = { 0 };
GameDifficulty Game::difficulty = GameDifficulty::MEDIUM;

void Game::Init() {
    backgroundMusic = LoadMusicStream("../assets/sounds/background_sound.mp3");
    SetMusicVolume(backgroundMusic, 1.0f);
    PlayMusicStream(backgroundMusic);
    backgroundMusic.looping = true;
    std::cout << "Music length (seconds): " << GetMusicTimeLength(backgroundMusic) << std::endl;
    std::cout << "Music looping enabled: " << backgroundMusic.looping << std::endl;

    currentScreen = std::make_unique<MenuScreen>();
    currentScreen->Init();
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
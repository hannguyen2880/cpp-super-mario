#include "GamePlayScreen.h"

GameplayScreen::GameplayScreen() {
    currentDifficulty = Game::GetDifficulty();
    currentMode = Game::GetGameplayMode();
    isPaused = false;
}

void GameplayScreen::Init() {
    if (currentMode == GameplayMode::NEW_GAME) {
        InitNewGame();
    } else {
        LoadSavedGame();
    }
    ConfigureDifficulty();
}

void GameplayScreen::ConfigureDifficulty() {
    // Use Build Method to build these level
    // LevelDirector = director
    // LevelBuilder* builder = nullptr

    switch (currentDifficulty) {
        case GameDifficulty::EASY:
            // builder = new EasyLevelBuilder();
            break;
        case GameDifficulty::MEDIUM:
            // Configure medium mode parameters
            break;
        case GameDifficulty::HARD:

            // Configure hard mode parameters
            break;
    }
}

void GameplayScreen::InitNewGame() {
    //score = 0;
    // Initialize new game state
}

void GameplayScreen::LoadSavedGame() {
    // Load saved game state from file/memory
}

void GameplayScreen::Update() {
    return;
}

void GameplayScreen::Draw() {
    return;
}

void GameplayScreen::Unload() {
    return;
}
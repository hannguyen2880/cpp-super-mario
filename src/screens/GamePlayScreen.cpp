#include "GamePlayScreen.h"

GameplayScreen::GameplayScreen()
    : currentDifficulty(GameConfig::getInstance().getDifficulty()),
      currentMode(GameConfig::getInstance().getGameplayMode()),
      currentCharacter(GameConfig::getInstance().getCharacter()),
      isPaused(false) {};

void GameplayScreen::Init() {
    if (currentMode == GameplayMode::SINGLE_PLAYER) {
        InitNewGame();
    } else {
        LoadSavedGame();
    }
}

void GameplayScreen::InitNewGame() {
    //gameManager->initWorld();
}

void GameplayScreen::LoadSavedGame() {
    //gameManager->loadGameState();
}

void GameplayScreen::Update() {
    bool secondPlayer = (currentMode == GameplayMode::MULTI_PLAYER);
    std::string mapFilePath;
    switch (currentDifficulty) {
        case GameDifficulty::EASY:
            mapFilePath = EASY_MAP;
            break;
        case GameDifficulty::MEDIUM:
            mapFilePath = MEDIUM_MAP;
            break;
        case GameDifficulty::HARD:
            mapFilePath = HARD_MAP;
            break;
    }
    GameManager gameManager(mapFilePath.c_str(), SCREEN_WIDTH, SCREEN_HEIGHT, secondPlayer);
    gameManager.mainLoop();
}

void GameplayScreen::Draw() {}

void GameplayScreen::Unload() {
    //gameManager.reset();
}
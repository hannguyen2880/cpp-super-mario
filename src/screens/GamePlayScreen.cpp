#include "GameplayScreen.h"
#include "../game/Game.h"
#include "../game/GameConfig.h"
#include "../game/GameManager.h"
#include "../game/State/MainMenuState.h"

GameplayScreen::GameplayScreen()
    : currentDifficulty(GameConfig::getInstance().getDifficulty()),
      currentMode(GameConfig::getInstance().getGameplayMode()),
      currentCharacter(GameConfig::getInstance().getCharacter()),
      isPaused(false),
      homeButton(HOME_BUTTON, 0, 45),
      pauseButton(PAUSE_BUTTON, 50, 45) {}

void GameplayScreen::Init() {
    CreateGameManager();
    std::cout << "DEBUG: GameplayScreen Init\n";
}

void GameplayScreen::CreateGameManager() {
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

    if (homeButton.Update()) {
        Game::SetState(std::make_unique<MainMenuState>());
        return;
    }
    if (pauseButton.Update()) {
        //isPaused = !isPaused;
        return;
    }
}

void GameplayScreen::Draw() {
    homeButton.Draw();
    pauseButton.Draw();
}

void GameplayScreen::Unload() {
}

GameplayScreen::~GameplayScreen() {
}
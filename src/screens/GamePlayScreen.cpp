#include "GamePlayScreen.h"
#include "../game/Game.h"
#include "../game/GameConfig.h"
#include "../game/GameManager.h"
#include "../game/State/MainMenuState.h"

GameplayScreen::GameplayScreen()
    : currentDifficulty(GameConfig::getInstance().getDifficulty()),
      currentMode(GameConfig::getInstance().getGameplayMode()),
      currentCharacter(GameConfig::getInstance().getCharacter()),
      isPaused(false),
      homeButton(nullptr) {}

void GameplayScreen::Init() {
    homeButton = new ImageButton(HOME_BUTTON, 0, 45);
    CreateGameManager();
    std::cout << "DEBUG: GameplayScreen Init\n";
}

void GameplayScreen::CreateGameManager() {
    if (gameManager) {
        std::cout << "WARNING: Creating new GameManager while old one exists" << std::endl;
        gameManager->cleanup();
        gameManager.reset();
    }

    bool secondPlayer = (currentMode == GameplayMode::MULTI_PLAYER);
    std::string mapFilePath;
    
    switch (currentDifficulty) {
        case GameDifficulty::EASY:
            mapFilePath = EASY_MAP;
            background = 1;
            break;
        case GameDifficulty::MEDIUM:
            mapFilePath = MEDIUM_MAP;
            background = 2;
            break;
        case GameDifficulty::HARD:
            mapFilePath = HARD_MAP;
            background = 3;
            break;
    }
    
    gameManager = std::make_unique<GameManager>(
        mapFilePath.c_str(), 
        SCREEN_WIDTH, 
        SCREEN_HEIGHT, 
        secondPlayer,
        background
    );
    gameManager->Init();
}

void GameplayScreen::Update() {
    if (gameManager) {
        if (gameManager->NeedsRestart()) {
            gameManager->cleanup();
            gameManager.reset();
            CreateGameManager();
            gameManager->Init();
        } else {
            if (homeButton && homeButton->Update()) {  // Add null check
                Game::SetState(std::make_unique<MainMenuState>());
            }
            gameManager->Update();
        }
    }
}

void GameplayScreen::Draw() {
    if (gameManager) {
        gameManager->Draw();
    }
    if (homeButton) {  // Add null check
        homeButton->Draw();
    }
}

void GameplayScreen::Unload() {
    if (homeButton) {
        delete homeButton;
        homeButton = nullptr;
    }
    std::cout << "DEBUG: GameplayScreen Unload\n";
}

GameplayScreen::~GameplayScreen() {
    Unload();
    std::cout << "DEBUG: GameplayScreen Destructor\n";
}
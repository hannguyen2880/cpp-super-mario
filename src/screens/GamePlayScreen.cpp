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
      homeButton(HOME_BUTTON, 0, 45),
      pauseButton(PAUSE_BUTTON, 0, 100),
      resumeButton(RESUME_BUTTON, 0, 100) {}

void GameplayScreen::Init() {
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
}

void GameplayScreen::Update() {
    if (gameManager) {
        if (gameManager->NeedsRestart()) {
            // Cleanup old game manager
            gameManager->cleanup();
            gameManager.reset();
            
            // Create new game manager
            CreateGameManager();
            gameManager->Init();
        } else {
            if (pauseButton.Update() && !isPaused) {
                isPaused = true;
                gameManager->setPause(true);
            }
            
            if (resumeButton.Update() && isPaused) {
                isPaused = false;
                gameManager->setPause(false);
            }

            if (homeButton.Update()) {
                Game::SetState(std::make_unique<MainMenuState>());
                return;
            }

            if (!isPaused) {
                gameManager->Update();
            }
        }
    }
}

void GameplayScreen::Draw() {
    if (gameManager) {
        gameManager->Draw();
        homeButton.Draw();
        
        if (isPaused) {
            resumeButton.Draw();
        } else {
            pauseButton.Draw();
        }
    }
}

void GameplayScreen::Unload() {
    std::cout << "DEBUG: GameplayScreen Unload\n";
    gameManager->saveScore();
    gameManager->printScore();
}

GameplayScreen::~GameplayScreen() {
    std::cout << "DEBUG: GameplayScreen Destructor\n";
}
#include "GameplayScreen.h"
#include "../game/Game.h"
#include "../game/GameConfig.h"
#include "../game/GameManager.h"

GameplayScreen::GameplayScreen()
    : currentDifficulty(GameConfig::getInstance().getDifficulty()),
      currentMode(GameConfig::getInstance().getGameplayMode()),
      currentCharacter(GameConfig::getInstance().getCharacter()),
      isPaused(false) {}

void GameplayScreen::Init() {
    CreateGameManager();
    std::cout << "DEBUG: GameplayScreen Init" << std::endl;
}

void GameplayScreen::CreateGameManager() {
    // if (gameManager) {
    //     std::cout << "WARNING: Creating new GameManager while old one exists" << std::endl;
    //     gameManager->cleanup();
    //     gameManager.reset();
    // }

    // bool secondPlayer = (currentMode == GameplayMode::MULTI_PLAYER);
    // std::string mapFilePath;
    
    // switch (currentDifficulty) {
    //     case GameDifficulty::EASY:
    //         mapFilePath = EASY_MAP;
    //         break;
    //     case GameDifficulty::MEDIUM:
    //         mapFilePath = MEDIUM_MAP;
    //         break;
    //     case GameDifficulty::HARD:
    //         mapFilePath = HARD_MAP;
    //         break;
    // }
    
    // gameManager = std::make_unique<GameManager>(
    //     mapFilePath.c_str(), 
    //     SCREEN_WIDTH, 
    //     SCREEN_HEIGHT, 
    //     secondPlayer
    // );
    // gameManager->Init();

    try {
        std::cout << "DEBUG: Starting GameManager creation..." << std::endl;
        
        GameConfig& config = Game::getConfig();
        bool secondPlayer = (config.getGameplayMode() == GameplayMode::MULTI_PLAYER);
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

        std::cout << "DEBUG: About to create GameManager with:" << std::endl;
        std::cout << "Map path: " << mapFilePath << std::endl;
        std::cout << "Screen size: " << SCREEN_WIDTH << "x" << SCREEN_HEIGHT << std::endl;
        std::cout << "Second player: " << secondPlayer << std::endl;
        std::cout << "DEBUG: Selected character: " << (config.getCharacter() == Character::MARIO ? "Mario" : "Luigi") << std::endl;
        gameManager = std::make_unique<GameManager>(
            mapFilePath.c_str(), 
            SCREEN_WIDTH, 
            SCREEN_HEIGHT, 
            secondPlayer
        );
        
        std::cout << "DEBUG: GameManager created successfully" << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "ERROR in CreateGameManager: " << e.what() << std::endl;
    } catch (...) {
        std::cout << "Unknown ERROR in CreateGameManager" << std::endl;
    }
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
            gameManager->Update();
        }
    }
}

void GameplayScreen::Draw() {
    if (gameManager) {
        gameManager->Draw();
    }
}

void GameplayScreen::Unload() {
    if (gameManager) {
        gameManager->cleanup();
        gameManager.reset();
    }
}
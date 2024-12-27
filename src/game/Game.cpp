#include "Game.h"
#include "State/MainMenuState.h"
#include "State/BeforeGameState.h"
#include "State/InstructionState.h"
#include "State/GameplayState.h"
#include "State/ScoreboardState.h"
#include <iostream>

std::unique_ptr<GameState> Game::currentState = nullptr;
GameDifficulty Game::difficulty = GameDifficulty::MEDIUM;
GameplayMode Game::gameplayMode = GameplayMode::SINGLE_PLAYER;
Character Game::character = Character::MARIO;

//ImageButton* Game::homeButton = nullptr;
//bool Game::isHomeButtonLoaded = false;

void Game::Init() {
    // try {
    //     homeButton = new ImageButton(HOME_BUTTON, 0, 45);
    //     //isHomeButtonLoaded = true;
    //     std::cout << "Home button loaded\n\n\n\n" << std::endl;
    // } catch (const std::exception& e) {
    //     std::cerr << "Failed to load home button: " << e.what() << std::endl;
    //     //isHomeButtonLoaded = false;
    // }

    currentState = std::make_unique<MainMenuState>();
    
    currentState->Init();
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
    
    //Unload();
    CloseAudioDevice();
    CloseWindow();
}

void Game::Update() {
    if (currentState) {
        currentState->Update();

        // if (dynamic_cast<GameplayState*>(currentState.get()) != nullptr) {
        //     if (homeButton->Update()) {
        //         std::cout << "Home button pressed\n\n\n\n";
        //         Game::SetState(std::make_unique<MainMenuState>());
        //         return;
        //     }
        // }
    }
}
void Game::Unload() {
    // if (homeButton) {
    //     delete homeButton;
    //     homeButton = nullptr;
    // }
}

void Game::Draw() {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    if (currentState) {
        currentState->Draw();
        // if (dynamic_cast<GameplayState*>(currentState.get()) != nullptr && homeButton) {
        //     homeButton->Draw();
        // }
    }
    EndDrawing();
}

void Game::SetState(std::unique_ptr<GameState> newState) {
    std::cout << "Setting state\n\n\n\n";
    if (currentState) {
        std::cout << "Unloading current state\n\n\n\n";
        currentState->Unload();
    } else {
        std::cout << "Current state is null\n\n\n\n";
    }

    std::cout << "Setting new state\n\n\n\n";
    currentState = std::move(newState);

    if (currentState) {
        currentState->Init();
    }
}

Game::~Game() {
    //Unload();
}

float Game::GetScreenWidth() { return 1.0 * SCREEN_WIDTH; }

float Game::GetScreenHeight() { return 1.0 * SCREEN_HEIGHT; }

GameDifficulty Game::GetDifficulty() { return difficulty; }

GameplayMode Game::GetGameplayMode() { return gameplayMode; }

Character Game::GetCharacter() { return character; }

GameConfig& Game::getConfig() { return GameConfig::getInstance(); }
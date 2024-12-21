#include "GameplayState.h"
#include "../../screens/GamePlayScreen.h"
#include <iostream>

void GameplayState::Init() {
    std::cout << "DEBUG: GameplayState Init\n";
    gameplayScreen = new GameplayScreen();
    gameplayScreen->Init();
}

void GameplayState::Update() {
    gameplayScreen->Update();
}

void GameplayState::Draw() {
    gameplayScreen->Draw();
}

void GameplayState::Unload() {
    std::cout << "DEBUG: GameplayState Unload\n";
    if (gameplayScreen) {
        gameplayScreen->Unload();
        delete gameplayScreen;
        gameplayScreen = nullptr;
    }
}

GameplayState::~GameplayState() {
    Unload();
}
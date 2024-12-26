#include "GameplayState.h"
#include "../../screens/GamePlayScreen.h"

void GameplayState::Init() {
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
    gameplayScreen->Unload();
    delete gameplayScreen;
    gameplayScreen = nullptr;
}

GameplayState::~GameplayState() {
    delete gameplayScreen;
}
#include "ScoreboardState.h"
#include "../../screens/ScoreboardScreen.h"

void ScoreboardState::Init() {
    scoreboardScreen = new ScoreboardScreen();
    scoreboardScreen->Init();
}

void ScoreboardState::Update() {
    scoreboardScreen->Update();
}

void ScoreboardState::Draw() {
    scoreboardScreen->Draw();
}

void ScoreboardState::Unload() {
    scoreboardScreen->Unload();
    delete scoreboardScreen;
    scoreboardScreen = nullptr;
}

ScoreboardState::~ScoreboardState() {
    delete scoreboardScreen;
}
#include "PauseState.h"
#include "../../screens/PauseScreen.h"

void PauseState::Init() {
    pauseScreen = new PauseScreen();
    pauseScreen->Init();
}

void PauseState::Update() {
    pauseScreen->Update();
}

void PauseState::Draw() {
    pauseScreen->Draw();
}

void PauseState::Unload() {
    pauseScreen->Unload();
    delete pauseScreen;
    pauseScreen = nullptr;
}

PauseState::~PauseState() {
    delete pauseScreen;
}
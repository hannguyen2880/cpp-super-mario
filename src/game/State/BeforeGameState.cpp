#include "BeforeGameState.h"
#include "../../screens/BeforeGameScreen.h"
#include <iostream>

void BeforeGameState::Init() {
    beforeGameScreen = new BeforeGameScreen();
    beforeGameScreen->Init();
}

void BeforeGameState::Update() {
    beforeGameScreen->Update();
}

void BeforeGameState::Draw() {
    beforeGameScreen->Draw();
}

void BeforeGameState::Unload() {
    if (beforeGameScreen) {
        beforeGameScreen->Unload();
        delete beforeGameScreen;
        beforeGameScreen = nullptr;
    }
}

BeforeGameState::~BeforeGameState() {
    Unload();
}
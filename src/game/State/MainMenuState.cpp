#include "MainMenuState.h"
#include "../../screens/MenuScreen.h"

MainMenuState::~MainMenuState() {
    Unload();
}

void MainMenuState::Init() {
    mainMenuScreen = new MenuScreen();
    mainMenuScreen->Init();
}

void MainMenuState::Update() {
    mainMenuScreen->Update();
}

void MainMenuState::Draw() {
    mainMenuScreen->Draw();
}

void MainMenuState::Unload() {
    if (mainMenuScreen) {
        mainMenuScreen->Unload();
        delete mainMenuScreen;
        mainMenuScreen = nullptr;
    }
}
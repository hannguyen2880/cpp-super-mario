#include "MainMenuState.h"
#include "../../screens/MenuScreen.h"

MainMenuState::~MainMenuState() {
    delete mainMenuScreen;
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
    mainMenuScreen->Unload();
    delete mainMenuScreen;
    mainMenuScreen = nullptr;
}
#include "Game.h"
#include "../screens/MenuScreen.h"
#include <iostream>

GameState Game::currentState = GameState::MAIN_MENU;
std::unique_ptr<Screen> Game::currentScreen = nullptr;

void Game::Init() {
    currentScreen = std::make_unique<MenuScreen>();
    currentScreen->Init();
}

void Game::Update() {
    if (currentScreen) {
        currentScreen->Update();
    }
}

void Game::Draw() {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    
    if (currentScreen) {
        currentScreen->Draw();
    }
    
    EndDrawing();
}

void Game::SetState(GameState newState) {
    currentState = newState;
    // Handle state change logic here
}
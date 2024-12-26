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

void Game::Init() {
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
    
    Unload();
    CloseAudioDevice();
    CloseWindow();
}

void Game::Update() {
    if (currentState) {
        currentState->Update();
    }
}
void Game::Unload() {
    if (currentState) {
        currentState->Unload();
    }
}

void Game::Draw() {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    if (currentState) {
        currentState->Draw();
    }
    EndDrawing();
}

void Game::SetState(std::unique_ptr<GameState> newState) {
    if (currentState) {
        currentState->Unload();
    }
    currentState = std::move(newState);
    if (currentState) {
        currentState->Init();
    }
}

float Game::GetScreenWidth() { return 1.0 * SCREEN_WIDTH; }

float Game::GetScreenHeight() { return 1.0 * SCREEN_HEIGHT; }

GameDifficulty Game::GetDifficulty() { return difficulty; }

GameplayMode Game::GetGameplayMode() { return gameplayMode; }

Character Game::GetCharacter() { return character; }

GameConfig& Game::getConfig() { return GameConfig::getInstance(); }
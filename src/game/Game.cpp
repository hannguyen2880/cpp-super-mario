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
    Game::difficulty = GameDifficulty::MEDIUM;
    Game::gameplayMode = GameplayMode::SINGLE_PLAYER;
    Game::character = Character::MARIO;
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
        if (IsKeyPressed(KEY_F1)) {
            //TakeScreenshot("screenshot.png");
            break;
        }
    }
    
    //Unload();
    CloseAudioDevice();
    CloseWindow();
}

void Game::Update() {
    if (currentState) {
        currentState->Update();
    }
}
// void Game::Unload() {
//     if (currentState) {
//         currentState->Unload();
//     }
// }

void Game::Draw() {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    if (currentState) {
        currentState->Draw();
    }
    EndDrawing();
}

void Game::SetState(std::unique_ptr<GameState> newState) {
    // if (currentState) {
    //     currentState->Unload();
    // }
    currentState = std::move(newState);
    if (currentState) {
        currentState->Init();
    }
}

Game::~Game() {
    // if (currentState) {
    //     currentState->Unload();
    // }
}
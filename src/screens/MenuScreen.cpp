#include "MenuScreen.h"
#include "../game/Game.h"
#include "../game/State/BeforeGameState.h"
#include "../game/State/InstructionState.h"
#include "../game/State/ScoreboardState.h"
#include <iostream>
#include <cmath>

MenuScreen::MenuScreen() : playButton(START_GAME_BUTTON, 228, 159),
                           instructionButton(INSTRUCTION_BUTTON, 228, 239),
                           scoreboardButton(SCOREBOARD_BUTTON, 228, 319) {
    originalMarioX = 55;
    originalMarioY = 199;
    cloud1X = 684;
    cloud1Y = 68;
    cloud1Speed = 0.5f;
    cloud1MovingRight = true;
    cloud2X = 950;
    cloud2Y = 27;
    cloud2Speed = 0.75f;
    cloud2MovingRight = true;
    framesCounter = 0;
    isLoading = true;
}

MenuScreen::~MenuScreen() {
    std::cout << "MenuScreen destroyed" << std::endl;
    Unload();
}

static bool firstLaunchCompleted = false;

void MenuScreen::Init() {
    background = LoadTexture(MAIN_MENU);
    loadingTexture = LoadTexture(LOADING_SCREEN);
    mario = LoadTexture(MARIO_MENU);
    cloud = LoadTexture(CLOUD);
    
    isLoading = !firstLaunchCompleted;
    if (isLoading) {
        firstLaunchCompleted = true;
    }
    loadingTime = 0;
    animationTime = 0;
    framesCounter = 0;
}

void MenuScreen::Unload() {
    UnloadTexture(loadingTexture);
    UnloadTexture(background);
    UnloadTexture(mario);
    UnloadTexture(cloud);
}

bool isRepeat = true;

void MenuScreen::Update() {
    if (isLoading) {
        if (framesCounter > 120) {
            isLoading = false;
        }
        loadingTime = (float)framesCounter / 60.0f;
        framesCounter++;
        return;
    }

    animationTime += GetFrameTime();
    originalMarioY = 199 + sin(animationTime * 2.0f) * 20;

    // Cloud 1 movement
    if (cloud1MovingRight) {
        cloud1X += cloud1Speed;
        if (cloud1X + cloud.width >= Game::GetScreenWidth()) {
            cloud1MovingRight = false;
        }
    } else {
        cloud1X -= cloud1Speed;
        if (cloud1X <= 640) {
            cloud1MovingRight = true;
        }
    }
    
    // Cloud 2 movement
    if (cloud2MovingRight) {
        cloud2X += cloud2Speed;
        if (cloud2X + cloud.width >= Game::GetScreenWidth()) {
            cloud2MovingRight = false;
        }
    } else {
        cloud2X -= cloud2Speed;
        if (cloud2X <= 640) {
            cloud2MovingRight = true;
        }
    }

    if (!isLoading) {
        if (playButton.Update()) {
            Game::SetState(std::make_unique<BeforeGameState>());
            return;
        }
        if (instructionButton.Update()) {
            Game::SetState(std::make_unique<InstructionState>());
            return;
        }
        if (scoreboardButton.Update()) {
            Game::SetState(std::make_unique<ScoreboardState>());
            return;
        }
    }
}

void MenuScreen::Draw() {
    if (isLoading) {
        DrawTexture(loadingTexture, 0, 0, WHITE);
        return;
    }

    DrawTexture(background, 0, 0, WHITE);
    DrawTexture(mario, originalMarioX, originalMarioY, WHITE);
    DrawTexture(cloud, cloud1X, cloud1Y, WHITE);
    DrawTexture(cloud, cloud2X, cloud2Y, WHITE);
    
    playButton.Draw();
    instructionButton.Draw();
    scoreboardButton.Draw();
}
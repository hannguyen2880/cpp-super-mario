// src/screens/MenuScreen.cpp
#include "MenuScreen.h"
#include "../game/Game.h"
#include <iostream>
#include <cmath>

MenuScreen::MenuScreen() {
    playButton = ImageButton("../assets/imgs/Buttons/StartGameButton.png", 228, 159);
    instructionButton = ImageButton("../assets/imgs/Buttons/InstructionButton.png", 228, 239);
    scoreboardButton = ImageButton("../assets/imgs/Buttons/ScoreboardButton.png", 228, 319);
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
    Unload();
}

static bool firstLaunchCompleted = false;

void MenuScreen::Init() {
    background = LoadTexture("../assets/imgs/menu-2.png");
    loadingTexture = LoadTexture("../assets/imgs/Loading_menu.png");
    mario = LoadTexture("../assets/imgs/Mario.png");
    cloud = LoadTexture("../assets/imgs/Clouds.png");

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
    //playButton.~ImageButton();
    //instructionButton.~ImageButton();
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
            Game::SetState(GameState::BEFOREGAME);
            return;
        }
        if (instructionButton.Update()) {
            Game::SetState(GameState::INSTRUCTIONS);
            return;
        }
        if (scoreboardButton.Update()) {
            Game::SetState(GameState::SCOREBOARD);
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
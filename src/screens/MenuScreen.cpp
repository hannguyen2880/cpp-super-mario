// src/screens/MenuScreen.cpp
#include "MenuScreen.h"
#include "../game/Game.h"
#include <iostream>
#include <cmath>

MenuScreen::MenuScreen() {
    const char* PLAY_TEXT = "Play Game";
    const char* INSTRUCTIONS_TEXT = "Instructions";
    const char* FONT_PATH = "../assets/fonts/comici.ttf";

    playButton = Button(PLAY_TEXT, 380, 220, 200, 50, FONT_PATH, ButtonStyle::GOLD_STYLE);
    instructionsButton = Button(INSTRUCTIONS_TEXT, 380, 290, 200, 50, FONT_PATH, ButtonStyle::GOLD_STYLE);

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
    time = 0;
    isLoading = true;
}

MenuScreen::~MenuScreen() {
    Unload();
}

void MenuScreen::Init() {
    background = LoadTexture("../assets/images/menu-2.png");
    loadingTexture = LoadTexture("../assets/images/Loading_menu.png");
    mario = LoadTexture("../assets/images/Mario.png");
    cloud = LoadTexture("../assets/images/Clouds.png");
}

void MenuScreen::Unload() {
    UnloadTexture(loadingTexture);
    UnloadTexture(background);
    UnloadTexture(mario);
    UnloadTexture(cloud);
}
void MenuScreen::Update() {
    if (framesCounter > 180) {
        isLoading = false;
    }

    time = (float)framesCounter / 60.0f;
    framesCounter++;

    originalMarioY = 199 + sin(time * 2.0f) * 20;

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
            Game::SetState(GameState::GAMEPLAY);
        }
        if (instructionsButton.Update()) {
            Game::SetState(GameState::INSTRUCTIONS);
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
    instructionsButton.Draw();
}
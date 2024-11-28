#include "MenuScreen.h"
#include "../game/Game.h"
#include "../raygui.h"
#include <iostream>
#include <unistd.h>
#include <cmath>

MenuScreen::MenuScreen() {
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

void MenuScreen::Init() {
    loadingTexture = LoadTexture("../assets/images/Loading_menu.png");
    background = LoadTexture("../assets/images/menu-2.png");
    if (background.id <= 0) {
        std::cout << "Failed to load background texture" << std::endl;
    }

    mario = LoadTexture("../assets/images/Mario.png");
    cloud = LoadTexture("../assets/images/Clouds.png");
    playBtnBounds = {Game::GetScreenWidth()/2 - 100, 
                     Game::GetScreenHeight()/2 - 50, 
                     200, 50};
    instructBtnBounds = {Game::GetScreenWidth()/2 - 100, 
                        Game::GetScreenHeight()/2 + 50, 
                        200, 50};
}

void MenuScreen::Update() {
    if (framesCounter > 180) {
        isLoading = false;
        //return;
    }

    // Update time
    time = (float)framesCounter / 60.0f;
    framesCounter++;

    // Mario movement (up and down)
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
}

void MenuScreen::Draw() {
    if (isLoading) {
        DrawTexture(loadingTexture, 0, 0, WHITE);
        return;
    }
    //DrawText("Menu Screen", 360, 200, 40, BLACK);
    DrawTexture(background, 0, 0, WHITE);
    DrawTexture(mario, originalMarioX, originalMarioY, WHITE);
    DrawTexture(cloud, cloud1X, cloud1Y, WHITE);
    DrawTexture(cloud, cloud2X, cloud2Y, WHITE);
    // Button logic
    if (GuiButton(playBtnBounds, "Play Game")) {
        Game::SetState(GameState::GAMEPLAY);
    }
    
    if (GuiButton(instructBtnBounds, "Instructions")) {
        Game::SetState(GameState::INSTRUCTIONS);
    }
}
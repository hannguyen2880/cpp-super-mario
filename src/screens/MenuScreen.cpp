#include "MenuScreen.h"
#include "../game/Game.h"
#include "../raygui.h"
#include <iostream>
#include <unistd.h>

MenuScreen::MenuScreen() {
    originalMarioX = 55;
    originalMarioY = 199;
    cloud1X = 649;
    cloud1Y = 72;
    cloud1Speed = 1.3f;
    cloud1MovingLeft = true;
    cloud2X = 845;
    cloud2Y = 23;
    cloud2Speed = 1.3f;
    cloud2MovingRight = true;
}

void MenuScreen::Init() {
    loadingTexture = LoadTexture("../assets/images/Loading_menu.png");
    if (loadingTexture.id <= 0) {
        std::cout << "Failed to load loading texture" << std::endl;
    }
    background = LoadTexture("../assets/images/menu-2.png");
    if (background.id <= 0) {
        std::cout << "Failed to load background texture" << std::endl;
    }

    isLoading = true;
    elapsedTime = 0.0f;

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
    if (isLoading) {
        elapsedTime += GetFrameTime();
        if (elapsedTime >= 3.0f) {
            isLoading = false;
        }
        return;
    }

    // Cloud 1 movement
    if (cloud1MovingLeft) {
        cloud1X += cloud1Speed;
        if (cloud1X + cloud.width >= Game::GetScreenWidth()) {
            cloud1MovingLeft = false;
        }
    } else {
        cloud1X -= cloud1Speed;
        if (cloud1X <= 640) {
            cloud1MovingLeft = true;
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
    
    // Button logic
    if (GuiButton(playBtnBounds, "Play Game")) {
        Game::SetState(GameState::GAMEPLAY);
    }
    
    if (GuiButton(instructBtnBounds, "Instructions")) {
        Game::SetState(GameState::INSTRUCTIONS);
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
}

void MenuScreen::Unload() {
    UnloadTexture(loadingTexture);
    UnloadTexture(background);
    UnloadTexture(mario);
    UnloadTexture(cloud);
}
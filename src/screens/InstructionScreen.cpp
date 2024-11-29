// src/screens/InstructionScreen.cpp
/*
#include "InstructionScreen.h"
#include "../game/Game.h"

InstructionScreen::InstructionScreen()
    : backButton("Back", 20, 480, 150, 40, "assets/fonts/comicz.ttf", ButtonStyle::GOLD_STYLE)
{
    panelTargetY = 50;          // Final position from top
    panelCurrentY = 600;        // Start below screen
    panelAlpha = 0.0f;         // Start fully transparent
    animationSpeed = 800.0f;    // Pixels per second
    isAnimating = true;
}

void InstructionScreen::Init() {
    background = LoadTexture("../assets/images/background_instruction.png");
    instructionPanel = LoadTexture("../assets/images/instruction_panel.png");
}

void InstructionScreen::Update() {
    float deltaTime = GetFrameTime();

    if (isAnimating) {
        // Update position
        float distance = panelTargetY - panelCurrentY;
        if (abs(distance) > 1.0f) {
            panelCurrentY += (distance * 5.0f * deltaTime);
        } else {
            panelCurrentY = panelTargetY;
        }

        // Update alpha
        panelAlpha = std::min(1.0f, panelAlpha + deltaTime * 2);

        // Check if animation is complete
        if (panelCurrentY == panelTargetY && panelAlpha >= 1.0f) {
            isAnimating = false;
        }
    }

    if (!isAnimating && backButton.Update()) {
        Game::SetState(GameState::MAIN_MENU);
    }
}

void InstructionScreen::Draw() {
    // Draw background
    DrawTexture(background, 0, 0, WHITE);

    // Draw instruction panel with current position and alpha
    Color panelColor = {255, 255, 255, (unsigned char)(panelAlpha * 255)};
    DrawTexture(instructionPanel, 
                (Game::GetScreenWidth() - instructionPanel.width) / 2,
                panelCurrentY, 
                panelColor);

    // Only draw back button when animation is complete
    if (!isAnimating) {
        backButton.Draw();
    }
}

InstructionScreen::~InstructionScreen() {
    UnloadTexture(background);
    UnloadTexture(instructionPanel);
}*/
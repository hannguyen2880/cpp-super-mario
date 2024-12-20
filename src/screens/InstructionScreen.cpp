#include "InstructionScreen.h"
#include "../game/Game.h"
#include "../game/State/MainMenuState.h"

InstructionScreen::InstructionScreen()
    :backButton(BACK_BUTTON, 570, 17)
{
    panelTargetY = 161;
    panelCurrentY = 600;
    panelAlpha = 0.0f;
    animationSpeed = 800.0f;
    isAnimating = true;
}

void InstructionScreen::Init() {
    background = LoadTexture(MENU_BACKGROUND);
    instructionPanel = LoadTexture(INSTRUCTION_PANEL);
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
        Game::SetState(std::make_unique<MainMenuState>());
    }
}

void InstructionScreen::Draw() {
    DrawTexture(background, 0, 0, WHITE);

    int panelX = 200;
    
    Color panelColor = {255, 255, 255, (unsigned char)(panelAlpha * 255)};
    DrawTexture(instructionPanel, 
                panelX,
                panelCurrentY,
                panelColor);

    backButton.Draw();
}

InstructionScreen::~InstructionScreen() {
    Unload();
}

void InstructionScreen::Unload() {
    UnloadTexture(background);
    UnloadTexture(instructionPanel);
}
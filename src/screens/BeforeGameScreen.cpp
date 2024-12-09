#include "BeforeGameScreen.h"
#include "../game/Game.h"

BeforeGameScreen::BeforeGameScreen()
    : yesButton("../assets/images/YesButton.png", 300, 390),
      noButton("../assets/images/NoButton.png", 500, 390),
      backButton("Back", 20, 480, 150, 40, ButtonStyle::GOLD_STYLE, 20),
      easyButton("Easy", 380, 200, 200, 50, ButtonStyle::GREEN_STYLE),
      mediumButton("Medium", 380, 280, 200, 50, ButtonStyle::GOLD_STYLE),
      hardButton("Hard", 380, 360, 200, 50, ButtonStyle::DEFAULT)
{
    panelTargetY = 161;
    panelCurrentY = 600;
    panelAlpha = 0.0f;
    animationSpeed = 800.0f;
    isAnimating = true;
}

void BeforeGameScreen::Init() {
    background = LoadTexture("../assets/images/Screen_background.png");
    resumeGamePanel = LoadTexture("../assets/images/ResumeGamePanel.png");
}

void BeforeGameScreen::Update() {
    float deltaTime = GetFrameTime();

    if (isAnimating) {
        float distance = panelTargetY - panelCurrentY;
        if (abs(distance) > 1.0f) {
            panelCurrentY += (distance * 5.0f * deltaTime);
        } else {
            panelCurrentY = panelTargetY;
        }

        panelAlpha = std::min(1.0f, panelAlpha + deltaTime * 2);

        if (panelCurrentY == panelTargetY && panelAlpha >= 1.0f) {
            isAnimating = false;
        }
        return;
    }

    if (currentPanel == PanelState::RESUME_PANEL) {
        if (yesButton.Update()) {
            Game::SetState(GameState::GAMEPLAY);
        }
        if (noButton.Update()) {
            currentPanel = PanelState::DIFFICULTY_PANEL;
            isAnimating = true;  // Trigger animation for new panel
            panelCurrentY = 600; // Reset position for new panel
        }
    }
    else if (currentPanel == PanelState::DIFFICULTY_PANEL) {
        if (easyButton.Update()) {
            Game::SetDifficulty(GameDifficulty::EASY);
            Game::SetState(GameState::GAMEPLAY);
        }
        if (mediumButton.Update()) {
            Game::SetDifficulty(GameDifficulty::MEDIUM);
            Game::SetState(GameState::GAMEPLAY);
        }
        if (hardButton.Update()) {
            Game::SetDifficulty(GameDifficulty::HARD);
            Game::SetState(GameState::GAMEPLAY);
        }
    }

    if (backButton.Update()) {
        Game::SetState(GameState::MAIN_MENU);
    }
}

void BeforeGameScreen::Draw() {
    DrawTexture(background, 0, 0, WHITE);

    Color panelColor = {255, 255, 255, (unsigned char)(panelAlpha * 255)};
    
    if (currentPanel == PanelState::RESUME_PANEL) {
        DrawTexture(resumeGamePanel, 228, panelCurrentY, panelColor);
        if (!isAnimating) {
            yesButton.Draw();
            noButton.Draw();
        }
    }
    else if (currentPanel == PanelState::DIFFICULTY_PANEL) {
        DrawRectangle(228, panelCurrentY, 504, 300, 
                     ColorAlpha(BLACK, panelAlpha * 0.7f));
        
        if (!isAnimating) {
            easyButton.Draw();
            mediumButton.Draw();
            hardButton.Draw();
        }
    }

    if (!isAnimating) {
        backButton.Draw();
    }
}

void BeforeGameScreen::Unload() {
    UnloadTexture(background);
    UnloadTexture(resumeGamePanel);
}

BeforeGameScreen::~BeforeGameScreen() {
    Unload();
}
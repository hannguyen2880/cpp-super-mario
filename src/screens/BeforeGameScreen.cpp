#include "BeforeGameScreen.h"
#include "../game/Game.h"
#include "../game/State/GameplayState.h"
#include "../game/State/MainMenuState.h"

BeforeGameScreen::BeforeGameScreen()
    : yesButton(YES_BUTTON, 280, 314),
      noButton(NO_BUTTON, 380, 314),
      backButton(BACK_BUTTON, 570, 17),
      easyButton(EASY_BUTTON, 260, 190),
      mediumButton(MEDIUM_BUTTON, 260, 250),
      hardButton(HARD_BUTTON, 260, 310),
      marioButton(MARIO_BUTTON, 380, 240),
      luigiButton(LUIGI_BUTTON, 240, 240),
      singlePlayerButton("1 PLAYER", 260, 220, 200, 50, ButtonStyle::BLUE_STYLE, 30),
      multiPlayerButton("2 PLAYERS", 260, 300, 200, 50, ButtonStyle::GREEN_STYLE, 30)
{
    panelTargetY = 172;
    panelCurrentY = 600;
    panelAlpha = 0.0f;
    animationSpeed = 800.0f;
    isAnimating = true;
    currentPanel = PanelState::RESUME_PANEL;
}

void BeforeGameScreen::Init() {
    background = LoadTexture(MENU_BACKGROUND);
    resumeGamePanel = LoadTexture(RESUMEGAME_PANEL);
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
            Game::SetState(std::make_unique<GameplayState>());
            GameConfig::getInstance().setGameplayMode(GameplayMode::RESUME_GAME);
        }
        if (noButton.Update()) {
            currentPanel = PanelState::PLAYER_COUNT_PANEL;
            isAnimating = true;
            panelCurrentY = 600;
        }
    }
    else if (currentPanel == PanelState::PLAYER_COUNT_PANEL) {
        if (singlePlayerButton.Update()) {
            GameConfig::getInstance().setGameplayMode(GameplayMode::SINGLE_PLAYER);
            currentPanel = PanelState::CHARACTER_SELECTION_PANEL;
            isAnimating = true;
            panelCurrentY = 600;
        }
        if (multiPlayerButton.Update()) {
            GameConfig::getInstance().setGameplayMode(GameplayMode::MULTI_PLAYER);
            currentPanel = PanelState::DIFFICULTY_PANEL;
            isAnimating = true;
            panelCurrentY = 600;
        }
    }
    else if (currentPanel == PanelState::CHARACTER_SELECTION_PANEL) {
        if (marioButton.Update()) {
            GameConfig::getInstance().setCharacter(Character::MARIO);
            currentPanel = PanelState::DIFFICULTY_PANEL;
            isAnimating = true;
            panelCurrentY = 600;
        }
        if (luigiButton.Update()) {
            GameConfig::getInstance().setCharacter(Character::LUIGI);
            currentPanel = PanelState::DIFFICULTY_PANEL;
            isAnimating = true;
            panelCurrentY = 600;
        }
    }
    else if (currentPanel == PanelState::DIFFICULTY_PANEL) {
        if (easyButton.Update()) {
            Game::getConfig().setDifficulty(GameDifficulty::EASY);
            Game::SetState(std::make_unique<GameplayState>());
        }
        if (mediumButton.Update()) {
            Game::getConfig().setDifficulty(GameDifficulty::MEDIUM);
            Game::SetState(std::make_unique<GameplayState>());
        }
        if (hardButton.Update()) {
            Game::getConfig().setDifficulty(GameDifficulty::HARD);
            Game::SetState(std::make_unique<GameplayState>());
        }
    }

    if (backButton.Update()) {
        Game::SetState(std::make_unique<MainMenuState>());
    }
}

void BeforeGameScreen::Draw() {
    DrawTexture(background, 0, 0, WHITE);

    Color panelColor = {255, 255, 255, (unsigned char)(panelAlpha * 255)};
    
    if (currentPanel == PanelState::RESUME_PANEL) {
        DrawTexture(resumeGamePanel, 200, panelCurrentY, panelColor);
        if (!isAnimating) {
            yesButton.Draw();
            noButton.Draw();
        }
    }
    else if (currentPanel == PanelState::PLAYER_COUNT_PANEL) {
        DrawRectangle(200, panelCurrentY, 318, 200, 
                     ColorAlpha(RAYWHITE, panelAlpha * 0.9f));
        DrawText("Select Players", 250, 180, 30, BLACK);
        if (!isAnimating) {
            singlePlayerButton.Draw();
            multiPlayerButton.Draw();
        }
    }
    else if (currentPanel == PanelState::CHARACTER_SELECTION_PANEL) {
        DrawRectangle(200, panelCurrentY, 318, 200, 
                     ColorAlpha(RAYWHITE, panelAlpha * 0.9f));
        DrawText("Select character", 220, 180, 30, BLACK);
        if (!isAnimating) {
            marioButton.Draw();
            luigiButton.Draw();
        }
    }
    else if (currentPanel == PanelState::DIFFICULTY_PANEL) {
        DrawRectangle(200, panelCurrentY, 318, 200, 
                     ColorAlpha(RAYWHITE, panelAlpha * 0.9f));
        if (!isAnimating) {
            easyButton.Draw();
            mediumButton.Draw();
            hardButton.Draw();
        }
    }

    backButton.Draw();
}

void BeforeGameScreen::Unload() {
    UnloadTexture(background);
    UnloadTexture(resumeGamePanel);
}

BeforeGameScreen::~BeforeGameScreen() {
    Unload();
}
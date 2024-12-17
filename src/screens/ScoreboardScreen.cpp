#include "ScoreboardScreen.h"
#include "../game/State/MainMenuState.h"
#include "../game/Game.h"

ScoreboardScreen::ScoreboardScreen()
    :backButton(BACK_BUTTON, 570, 17) {}

ScoreboardScreen::~ScoreboardScreen() {}

void ScoreboardScreen::Init() {}

void ScoreboardScreen::Update() {
    if (backButton.Update()) {
        Game::SetState(std::make_unique<MainMenuState>());
    }
}

void ScoreboardScreen::Draw() {
    backButton.Draw();
}

void ScoreboardScreen::Unload() {}
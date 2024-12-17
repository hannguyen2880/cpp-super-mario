#pragma once
#include "Screen.h"
#include "../game/State/GameState.h"
#include "../Constants.h"

#include "../State.h"

class GameplayScreen : public Screen {
private:
    GameDifficulty currentDifficulty;
    GameplayMode currentMode;
    Character currentCharacter;
    bool isPaused;

    void InitNewGame();
    void LoadSavedGame();

public:
    GameplayScreen();
    void Init() override;
    void Update() override;
    void Draw() override;
    void Unload() override;
};
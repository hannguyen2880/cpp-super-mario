#pragma once
#include "Screen.h"
#include "../game/GameState.h"
#include "../game/GameConfig.h"
#include "../game/GameManager.h"

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
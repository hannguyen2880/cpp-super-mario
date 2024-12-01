#pragma once
#include "Screen.h"
#include "../game/GameState.h"
#include "../game/Game.h"

class GameplayScreen : public Screen {
private:
    GameDifficulty currentDifficulty;
    GameplayMode currentMode;
    void InitNewGame();
    void LoadSavedGame();
    void ConfigureDifficulty();

public:
    GameplayScreen();
    void Init() override;
    void Update() override;
    void Draw() override;
    void Unload() override;
};
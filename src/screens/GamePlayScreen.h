#pragma once
#include "Screen.h"
#include "../game/GameState.h"
#include "../game/Game.h"
#include "../game/GameConfig.h"

class GameplayScreen : public Screen {
private:
    GameDifficulty currentDifficulty;
    GameplayMode currentMode;
    bool isPaused;
    void InitNewGame();
    void LoadSavedGame();
    void ConfigureDifficulty();

public:
    GameplayScreen();
    void InitializeBasedOnConfig();
    void Init() override;
    void Update() override;
    void Draw() override;
    void Unload() override;
};
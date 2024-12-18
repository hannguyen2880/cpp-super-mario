#pragma once
#include "../screens/Screen.h"
#include "../game/GameManager.h"
#include "../game/GameConfig.h"
#include "../Constants.h"
#include <memory>

class GameplayScreen : public Screen {
private:
    std::unique_ptr<GameManager> gameManager;
    GameDifficulty currentDifficulty;
    GameplayMode currentMode;
    Character currentCharacter;
    bool isPaused;
    void CreateGameManager();

public:
    GameplayScreen();
    void Init() override;
    void Update() override;
    void Draw() override;
    void Unload() override;
};

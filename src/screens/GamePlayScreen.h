#pragma once
#include "../screens/Screen.h"
#include "../game/GameManager.h"
#include "../game/GameConfig.h"
#include "../Constants.h"
#include <memory>
#include "../ui/ImageButton.h"

class GameplayScreen : public Screen {
private:
    std::optional<GameManager> gameManager;
    GameDifficulty currentDifficulty;
    GameplayMode currentMode;
    Character currentCharacter;
    bool isPaused;
    ImageButton homeButton, pauseButton;
    void CreateGameManager();

public:
    GameplayScreen();
    ~GameplayScreen();
    void Init() override;
    void Update() override;
    void Draw() override;
    void Unload() override;
};

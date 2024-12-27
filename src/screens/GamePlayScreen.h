#pragma once
#include "../screens/Screen.h"
#include "../game/GameManager.h"
#include "../game/GameConfig.h"
#include "../Constants.h"
#include <memory>
#include "../ui/ImageButton.h"

class GameplayScreen : public Screen {
private:
    std::unique_ptr<GameManager> gameManager;
    GameDifficulty currentDifficulty;
    GameplayMode currentMode;
    Character currentCharacter;
    bool isPaused;
    int background;
    ImageButton homeButton;
    void CreateGameManager();

public:
    GameplayScreen();
    virtual ~GameplayScreen();
    void Init() override;
    void Update() override;
    void Draw() override;
    void Unload() override;
};

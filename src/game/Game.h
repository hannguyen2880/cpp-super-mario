#pragma once
#include "GameState.h"
#include "../screens/Screen.h"
#include <memory>
#include "../Constants.h"
#include "GameConfig.h"

class Game {
private:
    static GameState currentState;
    static std::unique_ptr<Screen> currentScreen;
    static GameDifficulty difficulty;
    static GameplayMode gameplayMode;
    static Character character;
    
public:
    Game(){};
    static void Init();
    static void Update();
    static void Draw();
    static void SetState(GameState newState);
    static void Unload();
    static void Run();

    static float GetScreenWidth() { return 1.0 * SCREEN_WIDTH; }
    static float GetScreenHeight() { return 1.0 * SCREEN_HEIGHT; }
    static GameDifficulty GetDifficulty() { return difficulty; }
    static GameplayMode GetGameplayMode() { return gameplayMode; }
    static Character GetCharacter() { return character; }

    static GameConfig& getConfig() { return GameConfig::getInstance(); }
};
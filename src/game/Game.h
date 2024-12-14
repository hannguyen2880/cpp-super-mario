#pragma once
#include "GameState.h"
#include "../screens/Screen.h"
#include <memory>
#include "../audio/AudioManager.h"
class Game {
private:
    static GameState currentState;
    static std::unique_ptr<Screen> currentScreen;
    static const int screenWidth = 960;
    static const int screenHeight = 540;
    static GameDifficulty difficulty;
    static GameplayMode gameplayMode;
    static Character character;
    
public:
    static void Init();
    static void Update();
    static void Draw();
    static void SetState(GameState newState);
    static void Unload();
    static void Run();

    static float GetScreenWidth() { return 1.0 * screenWidth; }
    static float GetScreenHeight() { return 1.0 * screenHeight; }
    static GameDifficulty GetDifficulty() { return difficulty; }
    static GameplayMode GetGameplayMode() { return gameplayMode; }
    static Character GetCharacter() { return character; }

    static void SetDifficulty(GameDifficulty diff);
    static void SetGameplayMode(GameplayMode mode);
    static void SetCharacter(Character charac);
};
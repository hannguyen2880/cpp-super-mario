#pragma once
#include "GameState.h"
#include "../screens/Screen.h"
#include <memory>

class Game {
private:
    static GameState currentState;
    static std::unique_ptr<Screen> currentScreen;
    static const int screenWidth = 960;
    static const int screenHeight = 540;
    static GameDifficulty difficulty;
    static GameplayMode gameplayMode;

    static Music backgroundMusic;
    //static Sound jumpSound;
    //static Sound coinSound;
    
public:
    static void Init();
    static void Update();
    static void Draw();
    static void SetState(GameState newState);
    static void Unload();
    static void Run();
    //static void PlaySound(const char* soundName);

    static float GetScreenWidth() { return 1.0 * screenWidth; }
    static float GetScreenHeight() { return 1.0 * screenHeight; }
    static void SetDifficulty(GameDifficulty diff);
    static GameDifficulty GetDifficulty() { return difficulty; }
    static GameplayMode GetGameplayMode() { return gameplayMode; }
    static void SetGameplayMode(GameplayMode mode) { gameplayMode = mode; }
};
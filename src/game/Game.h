/**
 * @startuml
 * class Game {
 *     +Game()
 *     +static void Init()
 *     +static void Update()
 *     +static void Draw()
 *     +static void SetState(std::unique_ptr<GameState> newState)
 *     +static void Unload()
 *     +static void Run()
 *     +static float GetScreenWidth()
 *     +static float GetScreenHeight()
 *     +static GameDifficulty GetDifficulty()
 *     +static GameplayMode GetGameplayMode()
 *     +static Character GetCharacter()
 *     +static GameConfig& getConfig()
 *     -static std::unique_ptr<GameState> currentState
 *     -static GameDifficulty difficulty
 *     -static GameplayMode gameplayMode
 *     -static Character character
 * }
 * 
 * class GameConfig {
 * }
 * 
 * class GameState {
 * }
 * 
 * Game *-- GameConfig : composes
 * Game *-- GameState : composes
 * @enduml
 */

#ifndef GAME_H
#define GAME_H
#include "../screens/Screen.h"
#include <memory>
#include "../Constants.h"
#include "GameConfig.h"
#include "../State.h"

class Game {
private:
    static std::unique_ptr<GameState> currentState;
    static GameDifficulty difficulty;
    static GameplayMode gameplayMode;
    static Character character;
    
public:
    Game(){};
    static void Init();
    static void Update();
    static void Draw();
    static void SetState(std::unique_ptr<GameState> newState);
    static void Unload();
    static void Run();

    static float GetScreenWidth() { return 1.0 * SCREEN_WIDTH; }
    static float GetScreenHeight() { return 1.0 * SCREEN_HEIGHT; }
    static GameDifficulty GetDifficulty() { return difficulty; }
    static GameplayMode GetGameplayMode() { return gameplayMode; }
    static Character GetCharacter() { return character; }

    static GameConfig& getConfig() { return GameConfig::getInstance(); }
};
#endif // GAME_H
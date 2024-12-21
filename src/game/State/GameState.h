/**
 * @startuml
 * class GameState {
 *     +void Init()
 *     +void Update()
 *     +void Draw()
 *     +void Unload()
 *     +~GameState()
 * }
 * 
 * enum GameStateType {
 *     LOGO
 *     MAIN_MENU
 *     BEFOREGAME
 *     INSTRUCTIONS
 *     SCOREBOARD
 *     GAMEPLAY
 * }
 * 
 * enum GameDifficulty {
 *     EASY
 *     MEDIUM
 *     HARD
 * }
 * 
 * enum GameplayMode {
 *     RESUME_GAME
 *     SINGLE_PLAYER
 *     MULTI_PLAYER
 * }
 * 
 * enum Character {
 *     MARIO
 *     LUIGI
 * }
 * @enduml
 */

#pragma once

class GameState {
public:
    virtual void Init() = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0;
    virtual void Unload() = 0;
    virtual ~GameState() = default;
};

enum class GameStateType {
    LOGO,
    MAIN_MENU,
    BEFOREGAME,
    INSTRUCTIONS,
    SCOREBOARD,
    GAMEPLAY
};

enum class GameDifficulty {
    EASY,
    MEDIUM,
    HARD
};

enum class GameplayMode {
    RESUME_GAME,
    SINGLE_PLAYER,
    MULTI_PLAYER
};

enum class Character {
    MARIO,
    LUIGI
};
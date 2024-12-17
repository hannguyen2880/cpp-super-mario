#pragma once

enum class GameState {
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
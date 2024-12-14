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
    NEW_GAME,
    RESUME_GAME
};

enum class Character {
    MARIO,
    LUIGI
};
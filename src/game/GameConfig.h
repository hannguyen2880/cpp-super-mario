#pragma once
#include "State/GameState.h"
#include <string>

class GameConfig {
public:
    static GameConfig& getInstance();

    void setDifficulty(GameDifficulty difficulty);
    GameDifficulty getDifficulty() const;

    void setGameplayMode(GameplayMode mode);
    GameplayMode getGameplayMode() const;

    void setCharacter(Character character);
    Character getCharacter() const;

private:
    GameConfig() = default;
    GameDifficulty difficulty;
    GameplayMode gameplayMode;
    Character character;
    std::string mapFilePath;
};
#pragma once
#include "GameState.h"
#include <string>

class GameConfig {
public:
    static GameConfig& getInstance() {
        static GameConfig instance;
        return instance;
    }

    void setDifficulty(GameDifficulty difficulty) { this->difficulty = difficulty; }
    GameDifficulty getDifficulty() const { return difficulty; }

    void setGameplayMode(GameplayMode mode) { this->gameplayMode = mode; }
    GameplayMode getGameplayMode() const { return gameplayMode; }

    void setCharacter(Character character) { this->character = character; }
    Character getCharacter() const { return character; }

private:
    GameConfig() = default;
    GameDifficulty difficulty;
    GameplayMode gameplayMode;
    Character character;
    std::string mapFilePath;
};
#pragma once
#include "State/GameState.h"
#include <string>
/**
 * @startuml
 * class GameConfig {
 *     +static GameConfig& getInstance()
 *     +void setDifficulty(GameDifficulty difficulty)
 *     +GameDifficulty getDifficulty() const
 *     +void setGameplayMode(GameplayMode mode)
 *     +GameplayMode getGameplayMode() const
 *     +void setCharacter(Character character)
 *     +Character getCharacter() const
 *     -GameConfig()
 *     -GameDifficulty difficulty
 *     -GameplayMode gameplayMode
 *     -Character character
 *     -std::string mapFilePath
 * }
 * @enduml
 */


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
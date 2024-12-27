#include "GameConfig.h"

GameConfig& GameConfig::getInstance() {
        static GameConfig instance;
        return instance;
}

void GameConfig::setDifficulty(GameDifficulty difficulty) { this->difficulty = difficulty; }
GameDifficulty GameConfig::getDifficulty() const { return difficulty; }

void GameConfig::setGameplayMode(GameplayMode mode) { this->gameplayMode = mode; }
GameplayMode GameConfig::getGameplayMode() const { return gameplayMode; }

void GameConfig::setCharacter(Character character) { this->character = character; }
Character GameConfig::getCharacter() const { return character; }
#include "GameConfig.h"

float GameConfig::getEnemySpeed() {
    switch (difficulty) {
        case GameDifficulty::EASY: return 1.0f;
        case GameDifficulty::MEDIUM: return 1.5f;
        case GameDifficulty::HARD: return 2.0f;
        default: return 1.0f;
    }
}

int GameConfig::getInitialLives() {
    switch (difficulty) {
        case GameDifficulty::EASY: return 5;
        case GameDifficulty::MEDIUM: return 4;
        case GameDifficulty::HARD: return 3;
        default: return 3;
    }
}

void GameConfig::syncWithGameState() {
    difficulty = Game::GetDifficulty();
    character = Game::GetCharacter();
    mode = Game::GetGameplayMode();
}

void GameConfig::saveGameState(const PlayerState& state) {
    playerState = state;
    hasSavedGame = true;
}
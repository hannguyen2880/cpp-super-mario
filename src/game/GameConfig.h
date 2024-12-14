#include "GameState.h"
#include "Game.h"

struct PlayerState {
    float posX = 0.0f;
    float posY = 0.0f;
    int score = 0;
    int lives = 3;
};

class GameConfig {
private:
    static GameConfig* instance;
    
    GameDifficulty difficulty;
    Character character;
    GameplayMode mode;
    PlayerState playerState;
    bool hasSavedGame;

    GameConfig() : 
        difficulty(GameDifficulty::MEDIUM),
        character(Character::MARIO),
        mode(GameplayMode::NEW_GAME),
        hasSavedGame(false) {}

public:
    static GameConfig* getInstance() {
        if (instance == nullptr) {
            instance = new GameConfig();
        }
        return instance;
    }
    void saveGameState(const PlayerState& state);
    float getEnemySpeed();

    int getInitialLives();
    void syncWithGameState();
    PlayerState loadGameState() const {
        return playerState;
    }
    bool hasExistingSave() const { return hasSavedGame; }
};

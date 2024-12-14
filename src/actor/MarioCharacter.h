#pragma once
#include "CharacterActor.h"
#include <vector>

class MarioCharacter : public CharacterActor {
private:
    int lives;
    int score;
    bool isInvincible;
    float invincibilityTimer;

public:
    MarioCharacter(std::vector<std::string> spritePathsLeft, 
           std::vector<std::string> spritePathsRight);
    
    void Update(Camera2D& camera, TileMap2D& map);
    void TakeDamage();
    void AddScore(int points);
    //void CollectPowerup(PowerupType type);
    
    int getLives() const { return lives; }
    int getScore() const { return score; }
    bool getIsInvincible() const { return isInvincible; }
    void setVelocityX(float vx) { velocityX = vx; }
    void setVelocityY(float vy) { velocityY = vy; }
};
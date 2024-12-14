// Player.cpp
#include "MarioCharacter.h"

MarioCharacter::MarioCharacter(std::vector<std::string> spritePathsLeft, 
               std::vector<std::string> spritePathsRight)
    : CharacterActor(spritePathsLeft, spritePathsRight) {
    lives = 3;
    score = 0;
    isInvincible = false;
    invincibilityTimer = 0.0f;

	positionX = 0.0f;  // Slight offset from left
    positionY = 192;  // Place just above floor
    isOnGround = true;  // Start on ground
    velocityY = 0.0f;   // No initial vertical velocity
}

void MarioCharacter::Update(Camera2D& camera, TileMap2D& map) {
    UpdatePlayerAndCamera(camera, map);
    UpdateAnimation();
    
    // Update invincibility
    if (isInvincible) {
        invincibilityTimer -= GetFrameTime();
        if (invincibilityTimer <= 0) {
            isInvincible = false;
        }
    }
}

void MarioCharacter::TakeDamage() {
    if (!isInvincible) {
        lives--;
        isInvincible = true;
        invincibilityTimer = 2.0f; // 2 seconds of invincibility
        
        if (lives <= 0) {
            die();
        }
    }
}

void MarioCharacter::AddScore(int points) {
    score += points;
}
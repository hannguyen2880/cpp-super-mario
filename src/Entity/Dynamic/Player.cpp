#include "Player.h"

Player::Player(b2World* world, Vector2 position, Texture2D texture) : DynamicEntity(world, position, texture) {
    // Additional initialization if needed
}

Player::~Player() {
    // Additional cleanup if needed
}

void Player::Update() {
    // Implement player-specific update logic here
}
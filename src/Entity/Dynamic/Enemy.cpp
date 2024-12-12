#include "Enemy.h"

Enemy::Enemy(b2World* world, Vector2 position, Texture2D texture) : DynamicEntity(world, position, texture) {
    // Additional initialization if needed
}

Enemy::~Enemy() {
    // Additional cleanup if needed
}

void Enemy::Update() {
    // Implement enemy-specific update logic here
}

void Enemy::Draw() {
    //DynamicEntity::Draw();
}
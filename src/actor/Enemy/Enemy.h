// Enemy.h
#pragma once
#include "../Actor.h"
#include "../MarioCharacter.h"

enum class EnemyType {
    GOOMBA,
    KOOPA,
    PIRANHA_PLANT
};

class Enemy : public Actor {
protected:
    EnemyType type;
    bool isDead;
    float patrolDistance;
    float startX;
    float moveSpeed;

public:
    Enemy(EnemyType type, float x, float y);
    virtual ~Enemy() = default;

    virtual void Update();
    virtual void OnCollisionWithPlayer(MarioCharacter& player);
    virtual void Die();
    
    bool IsDead() const { return isDead; }
    EnemyType GetType() const { return type; }
};

// Specific enemy types
class Goomba : public Enemy {
public:
    Goomba(float x, float y) : Enemy(EnemyType::GOOMBA, x, y) {
        moveSpeed = 1.0f;
        patrolDistance = 100.0f;
    }
    
    void Update() override;
    void OnCollisionWithPlayer(MarioCharacter& player) override;
};

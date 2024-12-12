#pragma once
#include "../DynamicEntity.h"
#include "raylib-cpp.hpp"

class Player : public DynamicEntity {
public:
    Player();
    Player(b2World* world, Vector2 position, Texture2D texture);
    virtual ~Player();
    void Update() override;
    void Draw() override;
    void deletePhysicsBody();
    
    bool isOnGround;
    bool wasOnGround;
    void setPosition(const b2Vec2 &position);
	const b2Vec2& getVelocity() const;
    const b2Vec2& getPosition() const;
};
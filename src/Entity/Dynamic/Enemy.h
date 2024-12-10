#pragma once
#include "../DynamicEntity.h"

class Enemy : public DynamicEntity {
public:
    Enemy(b2World* world, Vector2 position, Texture2D texture);
    virtual ~Enemy();
    void Update() override;
};
#pragma once
#include "DynamicEntity.h"

class Player : public DynamicEntity {
public:
    Player(b2World* world, Vector2 position, Texture2D texture);
    virtual ~Player();
    void Update() override;
};
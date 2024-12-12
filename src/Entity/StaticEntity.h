#pragma once
#include "Entity.h"

class StaticEntity : public Entity {
public:
    StaticEntity(b2World* world, Vector2 position, Texture2D texture);
    virtual ~StaticEntity();
    virtual void Update() = 0;
    virtual void Draw() = 0;
};
#pragma once
#include "Entity.h"

class DynamicEntity : public Entity {
public:
    DynamicEntity(){};
    DynamicEntity(b2World* world, Vector2 position, Texture2D texture);
    virtual ~DynamicEntity();
    virtual void Update() = 0;
    virtual void Draw() = 0;
};
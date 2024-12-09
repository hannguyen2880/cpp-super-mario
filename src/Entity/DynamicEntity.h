#pragma once
#include "Entity.h"

class DynamicEntity : public Entity {
public:
    DynamicEntity(b2World* world, Vector2 position, Texture2D texture);
    virtual ~DynamicEntity();
};
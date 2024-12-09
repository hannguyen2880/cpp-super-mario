#pragma once
#include "Entity.h"

class KinematicEntity : public Entity {
public:
    KinematicEntity(b2World* world, Vector2 position, Texture2D texture);
    virtual ~KinematicEntity();
};
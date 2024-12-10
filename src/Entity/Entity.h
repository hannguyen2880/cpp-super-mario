#pragma once
#include <box2d/box2d.h>
#include <raylib.h>

class Entity {
protected:
    b2Body* body;
    Texture2D texture;
public:
    Entity(b2World* world, Vector2 position, Texture2D texture) {};
    virtual ~Entity() {
        UnloadTexture(texture);
    }
    virtual void Update() = 0;
    virtual void Draw() = 0;
};

void Entity::Draw() {
    Vector2 position = { body->GetPosition().x, body->GetPosition().y };
    DrawTexture(texture, position.x, position.y, WHITE);
}
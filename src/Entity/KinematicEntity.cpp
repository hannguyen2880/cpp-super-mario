#include "KinematicEntity.h"

KinematicEntity::KinematicEntity(b2World* world, Vector2 position, Texture2D texture) : Entity(world, position, texture) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_kinematicBody;
    bodyDef.position.Set(position.x, position.y);
    body = world->CreateBody(&bodyDef);

    b2PolygonShape boxShape;
    boxShape.SetAsBox(0.5f, 0.5f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &boxShape;
    fixtureDef.density = 0.0f;
    fixtureDef.friction = 0.3f;

    body->CreateFixture(&fixtureDef);
}

KinematicEntity::~KinematicEntity() {
    // Additional cleanup if needed
}
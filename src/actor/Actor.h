#pragma once

#include "../InputHandler.h"
#include "box2d/box2d.h"

class Actor {
protected:
    bool isAlive;
	b2Body* physicsBody;
public:
    bool isOnGround, wasOnGround;

    Actor();
    virtual ~Actor() {
        deletePhysicsBody();
    };
    void createPhysicsBody(b2World& world, float worldScale, const b2Vec2& position, const b2Vec2& velocity);
    void deletePhysicsBody();
    virtual void die();
    bool isMoving() const;
    const b2Vec2& getVelocity() const;
	void setVelocity(const b2Vec2& velocity);
    const b2Vec2& getPosition() const;
	void setPosition(const b2Vec2& position);
    virtual raylib::Rectangle getBoundingBox();
    virtual void drawBoundingBox(const Color& color);
};
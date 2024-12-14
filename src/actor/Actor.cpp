#include "Actor.h"

Actor::Actor() {
    isAlive = true;
    positionX = 0.0f;
    positionY = 0.0f;
    velocityX = 0.0f;
    velocityY = 0.0f;
    width = 0.0f;
    height = 0.0f;
    isOnGround = false;
}

bool Actor::isMoving() const {
    return (velocityX != 0.0f || velocityY != 0.0f);
}

void Actor::die() {
    isAlive = false;
}

Rectangle Actor::getBoundingBox() const {
    return Rectangle{
        positionX,
        positionY,
        width,
        height
    };
}

void Actor::drawBoundingBox(const Color& color) {
    Rectangle bounds = getBoundingBox();
    DrawRectangleLinesEx(bounds, 2.0f, color);
}

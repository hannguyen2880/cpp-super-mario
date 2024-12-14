#pragma once
#include "raylib-cpp.hpp"

class Actor {
protected:
    bool isAlive;
    float positionX, positionY;
    float velocityX;
    float velocityY;
    float width;
    float height;

public:
    bool isOnGround;
    
    Actor();
    virtual ~Actor() = default;

    // Basic getters and setters
    float getPositionX() const { return positionX; }
    float getPositionY() const { return positionY; }
    void setPosition(float x, float y) { positionX = x; positionY = y; }
    
    float getVelocityX() const { return velocityX; }
    float getVelocityY() const { return velocityY; }
    void setVelocity(float vx, float vy) { velocityX = vx; velocityY = vy; }
    
    bool isMoving() const;
    virtual void die();
    
    // Collision related
    virtual Rectangle getBoundingBox() const;
    virtual void drawBoundingBox(const Color& color);
    
    // Dimensions
    void setSize(float w, float h) { width = w; height = h; }
    float getWidth() const { return width; }
    float getHeight() const { return height; }
};

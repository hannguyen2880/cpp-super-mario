/**
 * @startuml
 * abstract class Button {
 *     +Button()
 *     +Button(float x, float y, float width, float height)
 *     +virtual ~Button()
 *     +virtual bool Update() = 0
 *     +virtual void Draw() = 0
 *     #Rectangle bounds
 *     #bool isHovered
 *     #bool isPressed
 * }
 * @enduml
 */
#pragma once
#include "raylib.h"
#include <string>
#include "ButtonStyle.h"

class Button {
protected:
    Rectangle bounds;
    bool isHovered, isPressed;

public:
    Button() {};
    Button(float x, float y, float width, float height) {
        bounds = {x, y, width, height};
        isHovered = false;
        isPressed = false;
    }
    virtual ~Button() {};

    virtual bool Update() = 0;
    virtual void Draw() = 0;
};
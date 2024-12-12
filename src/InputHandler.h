#pragma once
#include "raylib/raylib-cpp.hpp"

class InputHandler {
public:
    bool isJumpPressed() const;
    bool isMoveLeftPressed() const;
    bool isMoveRightPressed() const;
    bool isMoveDownPressed() const;
    bool isActionPressed() const;
};


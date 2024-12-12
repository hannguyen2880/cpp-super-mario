#include "InputHandler.h"

bool InputHandler::isJumpPressed() const {
    return IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_UP);
}

bool InputHandler::isMoveLeftPressed() const {
    return IsKeyDown(KEY_LEFT);
}

bool InputHandler::isMoveRightPressed() const {
    return IsKeyDown(KEY_RIGHT);
}

bool InputHandler::isMoveDownPressed() const {
    return IsKeyDown(KEY_DOWN);
}

bool InputHandler::isActionPressed() const {
    return IsKeyPressed(KEY_ENTER);
}

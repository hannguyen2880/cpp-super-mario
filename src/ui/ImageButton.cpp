#include "ImageButton.h"
#include <iostream>

ImageButton::ImageButton(const char* texturePath, float x, float y) : Button(x, y, 0, 0), pathTexture(texturePath) {
    texture = LoadTexture(pathTexture);
    bounds.width = (float)texture.width;
    bounds.height = (float)texture.height;
    scale = 1.0f;
    tint = WHITE;
}

ImageButton::~ImageButton() {
    Unload();
}

void ImageButton::Unload() {
    UnloadTexture(texture);
}

bool ImageButton::Update() {
    Vector2 mousePoint = GetMousePosition();
    isHovered = CheckCollisionPointRec(mousePoint, bounds);
    
    if (isHovered) {
        scale = 1.1f;  // Grow when hovered
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            isPressed = true;
            tint = GRAY;
            scale = 0.9f;  // Shrink when pressed
        } else if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && isPressed) {
            isPressed = false;
            return true;
        }
    } else {
        isPressed = false;
        scale = 1.0f;
        tint = WHITE;
    }
    
    return false;
}

void ImageButton::Draw() {
    texture = LoadTexture(pathTexture);
    float width = texture.width * scale;
    float height = texture.height * scale;
    float x = bounds.x + (texture.width - width) / 2;
    float y = bounds.y + (texture.height - height) / 2;
    
    Rectangle source = {0, 0, (float)texture.width, (float)texture.height};
    Rectangle dest = {x, y, width, height};
    Vector2 origin = {0, 0};
    
    DrawTexturePro(texture, source, dest, origin, 0.0f, tint);
}
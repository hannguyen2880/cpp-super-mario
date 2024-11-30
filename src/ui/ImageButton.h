// include/ui/ImageButton.h
#pragma once
#include "raylib.h"
#include <string>

class ImageButton {
private:
    Rectangle bounds;
    Texture2D texture;
    const char* pathTexture;
    bool isHovered;
    bool isPressed;
    float scale;
    Color tint;

public:
    ImageButton() {};
    ImageButton(const char* texturePath, float x, float y);
    void Unload();
    ~ImageButton();
    bool Update();
    void Draw();
};
// src/ui/Button.cpp
#include "Button.h"
#include <iostream>

Button::Button(const char* buttonText, float x, float y, float width, float height, 
               const char* customFontPath, ButtonStyle buttonStyle, float size) {
    text = buttonText;
    bounds = {x, y, width, height};
    fontSize = size;
    fontPath = customFontPath;
    
    // Load font
    font = LoadFont(fontPath.c_str());
    if (font.baseSize == 0) {
        std::cout << "Failed to load font: " << fontPath << std::endl;
    }
    else std::cout << "Load successful" << std::endl;

    isHovered = false;
    isPressed = false;
    
    // Apply initial style
    SetStyle(buttonStyle);
}

void Button::SetStyle(ButtonStyle newStyle) {
    style = newStyle;
    ApplyStyle(style);
}

void Button::ApplyStyle(ButtonStyle style) {
    switch(style) {
        case ButtonStyle::GOLD_STYLE:
            normalColor = {255, 203, 0, 255};    // Gold
            hoverColor = {255, 213, 10, 255};    // Light Gold
            activeColor = {245, 193, 0, 255};    // Dark Gold
            textColor = BLACK;
            break;
            
        case ButtonStyle::BLUE_STYLE:
            normalColor = {0, 121, 241, 255};    // Blue
            hoverColor = {10, 131, 251, 255};    // Light Blue
            activeColor = {0, 111, 231, 255};    // Dark Blue
            textColor = WHITE;
            break;
            
        case ButtonStyle::GREEN_STYLE:
            normalColor = {0, 228, 48, 255};     // Green
            hoverColor = {10, 238, 58, 255};     // Light Green
            activeColor = {0, 218, 38, 255};     // Dark Green
            textColor = WHITE;
            break;
            
        case ButtonStyle::DEFAULT:
        default:
            normalColor = {230, 41, 55, 255};    // Red
            hoverColor = {240, 51, 65, 255};     // Light Red
            activeColor = {220, 31, 45, 255};    // Dark Red
            textColor = WHITE;
            break;
    }
}

void Button::SetCustomColors(Color normal, Color hover, Color active, Color text) {
    style = ButtonStyle::CUSTOM;
    normalColor = normal;
    hoverColor = hover;
    activeColor = active;
    textColor = text;
}

void Button::SetFont(const char* newFontPath) {
    UnloadFont(font);
    fontPath = newFontPath;
    font = LoadFont(fontPath.c_str());
}

bool Button::Update() {
    Vector2 mousePoint = GetMousePosition();
    isHovered = CheckCollisionPointRec(mousePoint, bounds);
    
    if (isHovered) {
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            isPressed = true;
        } else if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && isPressed) {
            isPressed = false;
            return true;
        }
    } else {
        isPressed = false;
    }
    
    return false;
}

void Button::Draw() {
    // Draw button background
    Color currentColor = normalColor;
    if (isPressed) currentColor = activeColor;
    else if (isHovered) currentColor = hoverColor;
    
    DrawRectangleRec(bounds, currentColor);
    
    // Draw text centered
    Vector2 textSize = MeasureTextEx(font, text.c_str(), fontSize, 1);
    float textX = bounds.x + (bounds.width - textSize.x) / 2;
    float textY = bounds.y + (bounds.height - textSize.y) / 2;
    
    DrawTextEx(font, text.c_str(), {textX, textY}, fontSize, 1, textColor);
}
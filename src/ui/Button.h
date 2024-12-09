#pragma once
#include "raylib.h"
#include <string>
#include "ButtonStyle.h"

class Button {
private:
    Rectangle bounds;
    std::string text;
    Color normalColor;
    Color hoverColor;
    Color activeColor;
    Color textColor;
    float fontSize;
    bool isHovered;
    bool isPressed;
    ButtonStyle style;

public:
    Button() {};
    Button(const char* buttonText, float x, float y, float width, float height, 
           ButtonStyle style = ButtonStyle::DEFAULT,
           float size = 20.0f);
    
    void SetStyle(ButtonStyle newStyle);
    void SetCustomColors(Color normal, Color hover, Color active, Color text);
    bool Update();
    void Draw();

private:
    void ApplyStyle(ButtonStyle style);
};
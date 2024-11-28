#pragma once
#include "raylib.h"
#include <string>

enum class ButtonStyle {
    DEFAULT,
    YELLOW,
    BLUE,
    GREEN,
    CUSTOM
};

class Button {
private:
    Rectangle bounds;
    std::string text;
    std::string fontPath;
    Font font;
    Color normalColor;
    Color hoverColor;
    Color activeColor;
    Color textColor;
    float fontSize;
    bool isHovered;
    bool isPressed;
    ButtonStyle style;

public:
    Button(const char* buttonText, float x, float y, float width, float height, 
           const char* fontPath = "assets/fonts/COMIC.ttf", 
           ButtonStyle style = ButtonStyle::DEFAULT,
           float size = 20.0f);
    ~Button();
    
    void SetStyle(ButtonStyle newStyle);
    void SetCustomColors(Color normal, Color hover, Color active, Color text);
    void SetFont(const char* newFontPath);
    bool Update();
    void Draw();

private:
    void ApplyStyle(ButtonStyle style);
};
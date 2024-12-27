#pragma once

#include "Button.h"
#include "ButtonStyle.h"

class FontButton : public Button {
private:
    std::string text;
    Color normalColor;
    Color hoverColor;
    Color activeColor;
    Color textColor;
    float fontSize;
    ButtonStyle style;

public:
    FontButton() {};
    FontButton(const char* buttonText, float x, float y, float width, float height, 
               ButtonStyle style = ButtonStyle::DEFAULT, float size = 20.0f);
    
    void SetStyle(ButtonStyle newStyle);
    void SetCustomColors(Color normal, Color hover, Color active, Color text);
    bool Update() override;
    void Draw() override;

private:
    void ApplyStyle(ButtonStyle style);
};
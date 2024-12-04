#pragma once
#include "Screen.h"
#include "../ui/Button.h"
#include "../ui/ImageButton.h"
#include <string>

class InstructionScreen : public Screen {
private:
    Texture2D background;
    Texture2D instructionPanel;
    //Button backButton;
    ImageButton backButton;

    float panelTargetY;     // Final Y position
    float panelCurrentY;    // Current Y position
    float panelAlpha;       // Transparency
    float animationSpeed;
    bool isAnimating;

public:
    InstructionScreen();
    ~InstructionScreen();
    void Init() override;
    void Update() override;
    void Draw() override;
    void Unload() override;
};

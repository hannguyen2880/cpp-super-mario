// include/screens/BeforeGameScreen.h
#pragma once
#include "Screen.h"
#include "../ui/ImageButton.h"
#include "../ui/Button.h"
#include <string>

class BeforeGameScreen : public Screen {
private:
    enum class PanelState {
        RESUME_PANEL,
        DIFFICULTY_PANEL
    };
    Button easyButton;
    Button mediumButton;
    Button hardButton;
    PanelState currentPanel;
    
    Texture2D background;
    Texture2D resumeGamePanel;
    
    ImageButton yesButton;
    ImageButton noButton;
    Button backButton;

    float panelTargetY;
    float panelCurrentY;
    float panelAlpha;
    float animationSpeed;
    bool isAnimating;

public:
    BeforeGameScreen();
    ~BeforeGameScreen();
    void Init() override;
    void Update() override;
    void Draw() override;
    void Unload() override;
};
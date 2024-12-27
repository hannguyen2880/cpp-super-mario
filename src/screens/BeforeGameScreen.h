#pragma once
#include "Screen.h"
#include "../ui/ImageButton.h"
#include "../ui/FontButton.h"
#include "../ui/Button.h"
#include <string>

#include "../State.h"

class BeforeGameScreen : public Screen {
private:
    enum class PanelState {
        RESUME_PANEL,
        DIFFICULTY_PANEL,
        CHARACTER_SELECTION_PANEL,
        PLAYER_COUNT_PANEL,
    };
    PanelState currentPanel;

    Texture2D background;
    Texture2D resumeGamePanel;
    
    ImageButton yesButton, noButton;
    ImageButton backButton;
    ImageButton easyButton, mediumButton, hardButton;
    ImageButton marioButton, luigiButton;
    FontButton singlePlayerButton;
    FontButton multiPlayerButton;

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
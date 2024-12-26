/**
 * @startuml
 * enum PanelState {
 *     STATE_ONE
 *     STATE_TWO
 *     // Add other states as needed
 * }
 * 
 * class Texture2D {
 * }
 * 
 * class ImageButton {
 * }
 * 
 * class FontButton {
 * }
 * 
 * class BeforeGameScreen extends Screen {
 *     + BeforeGameScreen()
 *     + void Init() <<override>>
 *     + void Update() <<override>>
 *     + void Draw() <<override>>
 *     + void Unload() <<override>>
 *     + ~BeforeGameScreen()
 *     - PanelState currentPanel
 *     - Texture2D background
 *     - Texture2D resumeGamePanel
 *     - ImageButton yesButton
 *     - ImageButton noButton
 *     - ImageButton backButton
 *     - ImageButton easyButton
 *     - ImageButton mediumButton
 *     - ImageButton hardButton
 *     - ImageButton marioButton
 *     - ImageButton luigiButton
 *     - FontButton singlePlayerButton
 *     - FontButton multiPlayerButton
 *     - float panelTargetY
 *     - float panelCurrentY
 * }
 * 
 * BeforeGameScreen "1" *-- "1" PanelState
 * BeforeGameScreen "1" *-- "1" Texture2D
 * BeforeGameScreen "1" *-- "1" ImageButton
 * BeforeGameScreen "1" *-- "1" FontButton
 * @enduml
 */
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
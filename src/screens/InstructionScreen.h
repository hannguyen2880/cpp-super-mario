/**
 * @startuml
 * !include Screen.h
 * 
 * class ImageButton {
 * }
 * 
 * class InstructionScreen extends Screen {
 *     + InstructionScreen()
 *     + ~InstructionScreen()
 *     + void Init() <<override>>
 *     + void Update() <<override>>
 *     + void Draw() <<override>>
 *     + void Unload() <<override>>
 *     - Texture2D background
 *     - Texture2D instructionPanel
 *     - ImageButton backButton
 *     - float panelTargetY
 *     - float panelCurrentY
 *     - float panelAlpha
 *     - float animationSpeed
 *     - bool isAnimating
 * }
 * 
 * InstructionScreen "1" *-- "1" ImageButton
 * @enduml
 */


#pragma once
#include "Screen.h"
#include "../ui/Button.h"
#include "../ui/ImageButton.h"
#include <string>

#include "../State.h"

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

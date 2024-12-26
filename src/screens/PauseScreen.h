/**
 * @startuml
 * class Screen {
 * }
 * 

 * class ImageButton {
 * }
 * 
 * class PauseScreen extends Screen {
 *     + PauseScreen()
 *     + ~PauseScreen()
 *     + void Init() <<override>>
 *     + void Update() <<override>>
 *     + void Draw() <<override>>
 *     + void Unload() <<override>>
 *     - Texture2D background
 *     - ImageButton resumeButton
 *     - ImageButton mainMenuButton
 * }
 * 
 * PauseScreen "1" *-- "1" ImageButton
 * @enduml
 */
#pragma once
#include "Screen.h"
#include <string>
#include "../ui/Button.h"
#include "../ui/ImageButton.h"
#include "../Constants.h"
#include <iostream>
#include "../State.h"

class PauseScreen: public Screen {
private:
    Texture2D background;
    ImageButton resumeButton;
    ImageButton mainMenuButton;
public:
    PauseScreen();
    ~PauseScreen();
    void Init() override;
    void Update() override;
    void Draw() override;
    void Unload() override;
};
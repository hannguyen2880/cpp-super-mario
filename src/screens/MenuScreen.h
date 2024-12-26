/**
 * @startuml
 * class Screen {
 * }
 * 

 * class ImageButton {
 * }
 * 
 * class MenuScreen extends Screen {
 *     + MenuScreen()
 *     + ~MenuScreen()
 *     + void Init() <<override>>
 *     + void Update() <<override>>
 *     + void Draw() <<override>>
 *     + void Unload() <<override>>
 *     - float cloud1Speed
 *     - float cloud2Speed
 *     - bool cloud1MovingRight
 *     - bool cloud2MovingRight
 *     - Rectangle playBtnBounds
 *     - Rectangle instructBtnBounds
 *     - Texture2D loadingTexture
 *     - bool isLoading
 *     - float loadingTime
 *     - float animationTime
 *     - int framesCounter
 *     - ImageButton playButton
 *     - ImageButton instructionButton
 *     - ImageButton scoreboardButton
 * }
 * 
 * MenuScreen "1" *-- "1" ImageButton
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

class MenuScreen : public Screen {
private:
    Texture2D background, mario, cloud;
    
    float originalMarioX, originalMarioY;
    float cloud1X, cloud1Y, cloud1Speed;
    float cloud2X, cloud2Y, cloud2Speed;
    bool cloud1MovingRight, cloud2MovingRight;
    
    Rectangle playBtnBounds;
    Rectangle instructBtnBounds;
    // for loading screen
    Texture2D loadingTexture;
    
    bool isLoading;
    float loadingTime, animationTime;
    int framesCounter;  // Add this for frame tracking

    ImageButton playButton;
    ImageButton instructionButton;
    ImageButton scoreboardButton;
public:
    MenuScreen();
    ~MenuScreen();
    
    void Init() override;
    void Update() override;
    void Draw() override;
    void Unload() override;
};
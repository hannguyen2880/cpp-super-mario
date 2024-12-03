#pragma once
#include "Screen.h"
#include <string>
#include "../ui/Button.h"
#include "../ui/ImageButton.h"

class MenuScreen : public Screen {
private:
    Texture2D background;
    Texture2D mario;
    Texture2D cloud;
    
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

public:
    MenuScreen();
    ~MenuScreen();
    
    void Init() override;
    void Update() override;
    void Draw() override;
    void Unload() override;
};
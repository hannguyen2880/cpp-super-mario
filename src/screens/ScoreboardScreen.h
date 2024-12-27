/**
 * @startuml
 * class Screen {
 * }
 * 

 * class ImageButton {
 * }
 * 
 * class ScoreboardScreen extends Screen {
 *     + ScoreboardScreen()
 *     + ~ScoreboardScreen()
 *     + void Init() <<override>>
 *     + void Update() <<override>>
 *     + void Draw() <<override>>
 *     + void Unload() <<override>>
 *     - Texture2D background
 *     - vector<Texture2D> placeTextures
 *     - ImageButton backButton
 *     - float frame_positionX_1st
 *     - float frame_positionY_1st
 *     - float text_positionX_1st
 *     - float text_positionY_1st
 *     - float frameWidth
 *     - float frameHeight
 *     - float textLeftMargin
 *     - float textRightMargin
 * }
 * 
 * ScoreboardScreen "1" *-- "1" ImageButton
 * @enduml
 */

#pragma once

#include "Screen.h"
#include <string>
#include "../ui/Button.h"
#include "../ui/ImageButton.h"
#include "../State.h"

#include <utility>
#include <vector>


class ScoreboardScreen : public Screen {
private:

    Texture2D background;
    std::vector<Texture2D> placeTextures;
    ImageButton backButton;
    float frame_positionX_1st;
    float frame_positionY_1st;
    float text_positionX_1st;
    float text_positionY_1st;
    float frameWidth;
    float frameHeight;
    float textLeftMargin;
    float textRightMargin;
    float textVerticalSpacing;
    std::vector<std::pair<std::string, int>> players; // vector of pairs of player names and scores

public:
    ScoreboardScreen();
    ~ScoreboardScreen();
    void Init() override;
    void Update() override;
    void Draw() override;
    void Unload() override;
    void loadScores();
};
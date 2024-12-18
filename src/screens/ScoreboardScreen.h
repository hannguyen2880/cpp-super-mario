#pragma once
#include "Screen.h"
#include "../ui/Button.h"
#include "../ui/ImageButton.h"
#include <string>
#include <utility>
#include <vector>
using namespace std;


class ScoreboardScreen : public Screen {
private:
    Texture2D background;
    vector<Texture2D> placeTextures;
    ImageButton backButton;
    float frame_positionX_1st;
    float frame_positionY_1st;
    float text_positionX_1st;
    float text_positionY_1st;
    float frameWidth;
    float frameHeight;
    float textVerticalSpacing;
    float textHorizontalSpacing;
    vector<pair<string, int>> players; // vector of pairs of player names and scores

public:
    ScoreboardScreen();
    ~ScoreboardScreen();
    void Init() override;
    void Update() override;
    void Draw() override;
    void Unload() override;
};

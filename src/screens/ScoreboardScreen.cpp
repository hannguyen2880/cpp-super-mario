#include "ScoreboardScreen.h"
#include "../game/Game.h"
#include <iostream>
#include "../game/State/MainMenuState.h"


ScoreboardScreen::ScoreboardScreen() : backButton(ImageButton(BACK_BUTTON, 570, 17))
{
    frame_positionX_1st = 204;
    frame_positionY_1st = 145;
    
}

void ScoreboardScreen::Init() {
    background = LoadTexture(SCOREBOARD_BACKGROUND);
    for (int i = 0; i < 5; i++) {
        const char* texturePath;
        switch (i) {
            case 0:
                texturePath = FRIST_PLACE;
                //std::cout << "Texture path: " << texturePath << endl;
                break;
            case 1:
                texturePath = SECOND_PLACE;
                //std::cout << "Texture path: " << texturePath << endl;
                break;
            case 2:
                texturePath = THIRD_PLACE;
                //std::cout << "Texture path: " << texturePath << endl;
                break;
            case 3:
                texturePath = FOURTH_PLACE;
                //std::cout << "Texture path: " << texturePath << endl;
                break;
            case 4:
                texturePath = FIFTH_PLACE;
                //std::cout << "Texture path: " << texturePath << endl;
                break;
        }
        placeTextures.push_back(LoadTexture(texturePath));
    }
    // get frame width and height from 1st place texture
    frameWidth = placeTextures[0].width;
    frameHeight = placeTextures[0].height;
    textVerticalSpacing = frameHeight;
    textLeftMargin = frame_positionX_1st + 50;
    textRightMargin= frame_positionX_1st + frameWidth - 100;
    std::string defaultName = "NULL";
    int defaultScore = 0;
    for(int i = 0; i < 5; i++){
        players.push_back(make_pair(defaultName, defaultScore));
    }
}

void ScoreboardScreen::Update() {
    if (backButton.Update()) {
        Game::SetState(std::make_unique<MainMenuState>());
    }

}

void ScoreboardScreen::Draw() {
    // draw the scoreboard, 1st place to 5th place, with player names and scores
    //player name and score are separated by distance of textHorizontalSpacing
    // each player is separated by distance of textVerticalSpacing
    // each frame is upon another, with 0 distance between them
    // the first frame is at position (frame_positionX_1st, frame_positionY_1st)
    // the next frames are at position (frame_positionX_1st, frame_positionY_1st + i * textVerticalSpacing)
    DrawTexture(background, 0, 0, WHITE);
    for (int i = 0; i < 5; i++) {
        DrawTexture(placeTextures[i], frame_positionX_1st, frame_positionY_1st + i * textVerticalSpacing, WHITE);
        // draw player name and score
        DrawText(players[i].first.c_str(), textLeftMargin,15 + frame_positionY_1st + i * textVerticalSpacing, 20, WHITE);
        DrawText(std::to_string(players[i].second).c_str(), textRightMargin,15 + frame_positionY_1st + i * textVerticalSpacing, 20, WHITE);
    }
    backButton.Draw();
}

void ScoreboardScreen::Unload() {
    UnloadTexture(background);
    for (int i = 0; i < 5; i++) {
        UnloadTexture(placeTextures[i]);
    }
}

ScoreboardScreen::~ScoreboardScreen() {
    Unload();
}

#pragma once
#include "GameState.h"

class ScoreboardScreen;

class ScoreboardState : public GameState {
private:
    ScoreboardScreen* scoreboardScreen;
public:
    void Init() override;
    void Update() override;
    void Draw() override;
    void Unload() override;
    ~ScoreboardState();
};
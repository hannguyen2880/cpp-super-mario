#pragma once
#include "GameState.h"
#include "../State.h"

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
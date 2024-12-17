#pragma once
#include "GameState.h"

#include "../State.h"

class BeforeGameState : public GameState {
private:
    BeforeGameScreen* beforeGameScreen;
public:
    void Init() override;
    void Update() override;
    void Draw() override;
    void Unload() override;
    ~BeforeGameState();
};

#pragma once
#include "GameState.h"

#include "State.h"

class PauseState : public GameState {
private:
    PauseScreen* pauseScreen;
public:
    void Init() override;
    void Update() override;
    void Draw() override;
    void Unload() override;
    ~PauseState();
};
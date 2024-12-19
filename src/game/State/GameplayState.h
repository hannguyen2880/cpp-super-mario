#pragma once
#include "GameState.h"
#include "State.h"

class GameplayState : public GameState {
private:
    GameplayScreen* gameplayScreen;

public:
    void Init() override;
    void Update() override;
    void Draw() override;
    void Unload() override;
    ~GameplayState();
};
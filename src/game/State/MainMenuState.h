#pragma once
#include "GameState.h"

#include "../State.h"

class MainMenuState : public GameState {
private:
    MenuScreen* mainMenuScreen;
public:
    void Init() override;
    void Update() override;
    void Draw() override;
    void Unload() override;
    ~MainMenuState();
};
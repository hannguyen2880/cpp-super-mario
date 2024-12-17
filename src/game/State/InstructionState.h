#pragma once
#include "GameState.h"

#include "../State.h"

class InstructionState : public GameState {
private:
    InstructionScreen* instructionScreen;
public:
    void Init() override;
    void Update() override;
    void Draw() override;
    void Unload() override;
    ~InstructionState();
};
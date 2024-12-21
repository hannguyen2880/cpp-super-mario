/**
 * @startuml
 * class InstructionState extends GameState {
 *     - InstructionScreen* instructionScreen
 *     + void Init() <<override>>
 *     + void Update() <<override>>
 *     + void Draw() <<override>>
 *     + void Unload() <<override>>
 *     + ~InstructionState()
 * }
 * 
 * InstructionState "1" *-- "1" InstructionScreen
 * @enduml
 */

#pragma once
#include "GameState.h"

#include "State.h"

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
/**
 * @startuml
 * class BeforeGameState extends GameState {
 *     - BeforeGameScreen* beforeGameScreen
 *     + void Init() <<override>>
 *     + void Update() <<override>>
 *     + void Draw() <<override>>
 *     + void Unload() <<override>>
 *     + ~BeforeGameState()
 * }
 * 
 * BeforeGameState "1" *-- "1" BeforeGameScreen
 * @enduml
 */

#pragma once
#include "GameState.h"

#include "State.h"

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

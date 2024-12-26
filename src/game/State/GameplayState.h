/**
 * @startuml
 * class GameplayState extends GameState {
 *     - GameplayScreen* gameplayScreen
 *     + void Init() <<override>>
 *     + void Update() <<override>>
 *     + void Draw() <<override>>
 *     + void Unload() <<override>>
 *     + ~GameplayState()
 * }
 * 
 * GameplayState "1" *-- "1" GameplayScreen
 * @enduml
 */
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
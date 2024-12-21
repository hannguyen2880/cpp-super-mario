#pragma once
#include "GameState.h"

#include "State.h"
/**
 * @startuml
 * class GameState {
 *     + void Init() <<abstract>>
 *     + void Update() <<abstract>>
 *     + void Draw() <<abstract>>
 *     + void Unload() <<abstract>>
 *     + ~GameState()
 * }
 * 
 * class PauseScreen {
 * }
 * 
 * class PauseState extends GameState {
 *     + void Init() <<override>>
 *     + void Update() <<override>>
 *     + void Draw() <<override>>
 *     + void Unload() <<override>>
 *     + ~PauseState()
 *     - PauseScreen* pauseScreen
 * }
 * 
 * PauseState "1" *-- "1" PauseScreen
 * @enduml
 */


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
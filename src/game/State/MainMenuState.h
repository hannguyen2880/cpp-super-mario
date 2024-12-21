/**
 * @startuml
 * class MainMenuState extends GameState {
 *     - MenuScreen* mainMenuScreen
 *     + void Init() <<override>>
 *     + void Update() <<override>>
 *     + void Draw() <<override>>
 *     + void Unload() <<override>>
 *     + ~MainMenuState()
 * }
 * 
 * MainMenuState "1" *-- "1" MenuScreen
 * @enduml
 */

#pragma once
#include "GameState.h"

#include "State.h"

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
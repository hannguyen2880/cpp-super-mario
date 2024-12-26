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
 * class ScoreboardScreen {
 * }
 * 
 * class ScoreboardState extends GameState {
 *     + void Init() <<override>>
 *     + void Update() <<override>>
 *     + void Draw() <<override>>
 *     + void Unload() <<override>>
 *     + ~ScoreboardState()
 *     - ScoreboardScreen* scoreboardScreen
 * }
 * 
 * ScoreboardState "1" *-- "1" ScoreboardScreen
 * @enduml
 */

#pragma once
#include "GameState.h"
#include "State.h"

class ScoreboardState : public GameState {
private:
    ScoreboardScreen* scoreboardScreen;
public:
    void Init() override;
    void Update() override;
    void Draw() override;
    void Unload() override;
    ~ScoreboardState();
};
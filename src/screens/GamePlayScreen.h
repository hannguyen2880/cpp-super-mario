/**
 * @startuml
 * class Screen {
 * }
 * 
 * class GameManager {
 * }
 * 
 * enum GameDifficulty {
 *     EASY
 *     MEDIUM
 *     HARD
 * }
 * 
 * enum GameplayMode {
 *     SINGLE_PLAYER
 *     MULTI_PLAYER
 * }
 * 
 * enum Character {
 *     MARIO
 *     LUIGI
 * }
 * 
 * class ImageButton {
 * }
 * 
 * class GameplayScreen extends Screen {
 *     + GameplayScreen()
 *     + ~GameplayScreen()
 *     + void Init() <<override>>
 *     + void Update() <<override>>
 *     + void Draw() <<override>>
 *     + void Unload() <<override>>
 *     - std::unique_ptr<GameManager> gameManager
 *     - GameDifficulty currentDifficulty
 *     - GameplayMode currentMode
 *     - Character currentCharacter
 *     - bool isPaused
 *     - ImageButton homeButton
 *     - void CreateGameManager()
 * }
 * 
 * GameplayScreen "1" *-- "1" GameManager
 * GameplayScreen "1" *-- "1" GameDifficulty
 * GameplayScreen "1" *-- "1" GameplayMode
 * GameplayScreen "1" *-- "1" Character
 * GameplayScreen "1" *-- "1" ImageButton
 * @enduml
 */

#pragma once
#include "../screens/Screen.h"
#include "../game/GameManager.h"
#include "../game/GameConfig.h"
#include "../Constants.h"
#include <memory>
#include "../ui/ImageButton.h"

class GameplayScreen : public Screen {
private:
    std::unique_ptr<GameManager> gameManager;
    GameDifficulty currentDifficulty;
    GameplayMode currentMode;
    Character currentCharacter;
    bool isPaused;
    ImageButton homeButton;
    void CreateGameManager();

public:
    GameplayScreen();
    virtual ~GameplayScreen();
    void Init() override;
    void Update() override;
    void Draw() override;
    void Unload() override;
};

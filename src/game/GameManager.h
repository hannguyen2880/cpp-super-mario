#ifndef MARIO_MAKER_GAME_H
#define MARIO_MAKER_GAME_H
#include <raylib.h>
#include <iostream>
#include "ECS.h"
#include "../Constants.h"
#include "../map/GameMap.h"
#include "../audio/AudioManager.h"
#include "renderers/MapRenderer.h"
#include "renderers/TextureRenderer.h"
#include "renderers/EnemiesRenderer.h"
#include "renderers/ObjectRenderer.h"
#include "renderers/TextRenderer.h"
#include "systems/camera/CameraSystem.h"
#include "systems/player/PlayerSystem.h"
#include "systems/physics/PhysicSystem.h"
#include "systems/animation/AnimationSystem.h"
#include "systems/tile/TileSystem.h"
#include "systems/timer/TimerSystem.h"
#include "systems/enemy/EnemySystem.h"
#include "systems/flag/FlagSystem.h"
#include "systems/IdsMap/IdsMapSystem.h"
#include "systems/score/ScoreSystem.h"
#include "systems/sound/SoundSystem.h"
#include "State/GameState.h"
#include "Game.h"
#include "GameConfig.h"

class GameManager {
public:
    GameManager(const char* mapName, const int screenWidth, const int screenHeight, bool secondPlayer);
    ~GameManager();

    void Init();
    void Update();
    void Draw();
    void cleanup();
    bool NeedsRestart() const;
    GameMap *getMap() const{ return pMap_; }

private:
    void initWorld();
    void initPlayers();
    void registerSystems();
    void handleInput();
    void initIdsMap();
    void render(float d);
    void initTextEntities();
    void startMusic();
    void updateMusicStream();
    void restartGame();
    void saveScore();
    void printScore();

    bool run;
    bool pause;
    bool restart;
    bool secondPlayer;
    const char* mapName;
    ECS::World* world_;
    GameMap* pMap_;
    size_t cameraId_;
    const int screenWidth_;
    const int screenHeight_;
    
    double previous;
    double lag;

    ECS::EntitySystem* animationSystem_;
    SoundSystem* soundSystem_;
    MapRenderer* mapRenderer;
    TextureRenderer* textureRenderer;
    EnemiesRenderer* enemiesRenderer;
    ObjectRenderer* objectRenderer;
    TextRenderer* textRenderer_;

    void initMarioPlayer(ECS::Entity* player, Vector2 position);
    void initLuigiPlayer(ECS::Entity* player, Vector2 position);
};


#endif

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

class GameManager {
public:
    GameManager(const char* mapName, const int screenWidth, const int screenHeight, bool secondPlayer);

    void mainLoop();

    virtual ~GameManager();

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

private:
    bool run;
    bool pause;
    bool secondPlayer;
    ECS::World* world_;
    GameMap* pMap_;
    size_t cameraId_;
    const int screenWidth_;
    const int screenHeight_;
    ECS::EntitySystem* animationSystem_;
    SoundSystem* soundSystem_;
    MapRenderer* mapRenderer;
    TextureRenderer* textureRenderer;
    EnemiesRenderer *enemiesRenderer;
    ObjectRenderer* objectRenderer;
    TextRenderer* textRenderer_;
    bool restart = false;
};


#endif

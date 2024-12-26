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
class WorldBuilder {
public:
    WorldBuilder& initPlayers(ECS::World*& world, GameMap*& pMap, bool secondPlayer);
    WorldBuilder& initCamera(World*& world,const int& screenWidth_, const int& screenHeight_, size_t& cameraID_);

    WorldBuilder& initIdsMap(ECS::World*& world, GameMap*& pMap);


    WorldBuilder& registerSystems(ECS::World*& world,const int& screenWidth_, const int& screenHeight_,GameMap*& pMap_, ECS::EntitySystem*& animationSystem_, SoundSystem*& soundSystem_);
    WorldBuilder& initTextEntities(ECS::World*& world, const int& screenWidth_);

    WorldBuilder& startMusic(ECS::World*& world);
    void initMarioPlayer(ECS::Entity*& player, Vector2 position);
    void initLuigiPlayer(ECS::Entity*& player, Vector2 position);

};

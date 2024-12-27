/**
 * @startuml
 * class GameManager {
 *     +GameManager(const char* mapName, const int screenWidth, const int screenHeight, bool secondPlayer)
 *     +~GameManager()
 *     +void Init()
 *     +void Update()
 *     +void Draw()
 *     +void cleanup()
 *     +bool NeedsRestart() const
 *     +GameMap* getMap() const
 *     -void initWorld()
 *     -void handleInput()
 *     -void render(float d)
 *     -void updateMusicStream()
 *     -void restartGame()
 *     -void saveScore()
 *     -void printScore()
 *     -bool run
 *     -bool pause
 *     -bool restart
 *     -bool secondPlayer
 *     -const char* mapName
 *     -ECS::World* world_
 *     -GameMap* pMap_
 *     -size_t cameraId_
 *     -const int screenWidth_
 *     -const int screenHeight_
 *     -double previous
 *     -double lag
 *     -ECS::EntitySystem* animationSystem_
 *     -SoundSystem* soundSystem_
 *     -MapRenderer* mapRenderer
 *     -TextureRenderer* textureRenderer
 *     -EnemiesRenderer* enemiesRenderer
 *     -ObjectRenderer* objectRenderer
 *     -TextRenderer* textRenderer_
 * }
 * 
 * class ECS::World {
 *     +static ECS::World* createWorld()
 *     +void destroyWorld()
 *     +void tick(float delta)
 *     +ECS::Entity* create()
 *     +void registerSystem(ECS::EntitySystem* system)
 *     +void disableSystem(ECS::EntitySystem* system)
 *     +ECS::Entity* getById(size_t id)
 *     +void emit(const Event& event)
 * }
 * 
 * class ECS::Entity {
 *     +size_t getEntityId()
 *     +void assign<Component>(Args&&... args)
 *     +bool has<Component>()
 *     +Component* get<Component>()
 * }
 * 
 * class ECS::EntitySystem {
 * }
 * 
 * class GameMap {
 * }
 * 
 * class SoundSystem extends ECS::EntitySystem {
 *     +SoundSystem()
 *     +~SoundSystem()
 *     +void configure(ECS::World* world)
 *     +void unconfigure(ECS::World* world)
 *     +void tick(ECS::World* world, float delta)
 * }
 * 
 * class MapRenderer {
 *     +MapRenderer(GameMap* map, const char* filepath)
 *     +~MapRenderer()
 *     +void render(ECS::World* world, float delta)
 *     +void renderBackground(ECS::World* world)
 * }
 * 
 * class TextureRenderer {
 *     +explicit TextureRenderer(const char* filepath)
 *     +~TextureRenderer()
 *     +void renderTexture(TextureId textureId, Rectangle dstRect, bool flipH = false, bool flipV = false)
 *     +void renderTextureEntities(ECS::World* world, float delta)
 *     +void renderTileCollisionRect(ECS::World* world)
 * }
 * 
 * class EnemiesRenderer {
 *     +explicit EnemiesRenderer(const char* filepath)
 *     +~EnemiesRenderer()
 *     +void renderUnderTileEnemies(ECS::World* world, float delta)
 *     +void renderOverTileEnemies(ECS::World* world, float delta)
 * }
 * 
 * class ObjectRenderer {
 *     +explicit ObjectRenderer(const char* filepath)
 *     +~ObjectRenderer()
 *     +void render(ECS::World* world)
 * }
 * 
 * class TextRenderer {
 *     +TextRenderer()
 *     +~TextRenderer()
 *     +void render(ECS::World* world)
 *     +void renderScoreTextComponents(ECS::World* world)
 * }
 * 
 * class CameraSystem extends ECS::EntitySystem {
 * }
 * 
 * class PlayerSystem extends ECS::EntitySystem {
 * }
 * 
 * class EnemySystem extends ECS::EntitySystem {
 * }
 * 
 * class AnimationSystem extends ECS::EntitySystem {
 * }
 * 
 * class IdsMapSystem extends ECS::EntitySystem {
 * }
 * 
 * class PhysicSystem extends ECS::EntitySystem {
 * }
 * 
 * class TileSystem extends ECS::EntitySystem {
 * }
 * 
 * class FlagSystem extends ECS::EntitySystem {
 * }
 * 
 * GameManager *-- ECS::World : composes
 * GameManager *-- GameMap : composes
 * GameManager *-- SoundSystem : composes
 * GameManager *-- ECS::EntitySystem : composes
 * GameManager *-- MapRenderer : composes
 * GameManager *-- TextureRenderer : composes
 * GameManager *-- EnemiesRenderer : composes
 * GameManager *-- ObjectRenderer : composes
 * GameManager *-- TextRenderer : composes
 * 
 * ECS::World *-- ECS::Entity
 * ECS::World *-- CameraSystem 
 * ECS::World *-- PlayerSystem
 * ECS::World *-- EnemySystem
 * ECS::World *-- AnimationSystem
 * ECS::World *-- IdsMapSystem
 * ECS::World *-- PhysicSystem
 * ECS::World *-- TileSystem
 * ECS::World *-- FlagSystem
 * 
 * @enduml
 */


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

]
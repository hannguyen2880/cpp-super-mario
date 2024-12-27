#include "GameManager.h"
#include "GameConfig.h"
#include "WorldBuilder.h"
#include <iostream>
#include <fstream>
#include <string>


void WorldBuilder::initMarioPlayer(ECS::Entity *&player, Vector2 position) {
    player->getEntityId();
    player->assign<PlayerComponent>();
    player->assign<AABBComponent>(
            Rectangle {
                    position.x * 32,
                    position.y * 32,
                    32,
                    32});
    player->assign<TextureComponent>(MARIO_STAND);
    //player->assign<LeadCameraComponent>();
    player->assign<CommandComponent>(std::map<Command, int> {
            {JUMP, KEY_UP},
            {MOVE_LEFT, KEY_LEFT},
            {MOVE_RIGHT, KEY_RIGHT},
            {DUCK, KEY_DOWN},
            {SPRINT, KEY_LEFT_SHIFT},
            {SHOOT, KEY_Z}
    });
    player->assign<GravityComponent>();
    player->assign<SolidComponent>();
    player->assign<KineticComponent>(0.0f, 0.0f);
    player->assign<MarioComponent>();
}

void WorldBuilder::initLuigiPlayer(ECS::Entity *&player, Vector2 position) {
    player->getEntityId();
    player->assign<PlayerComponent>();
    player->assign<AABBComponent>(
            Rectangle {
                    position.x * 32,
                    position.y * 32,
                    32,
                    32});
    player->assign<TextureComponent>(LUIGI_STAND);
    player->assign<CommandComponent>(std::map<Command, int> {
            {JUMP, KEY_W},
            {MOVE_LEFT, KEY_A},
            {MOVE_RIGHT, KEY_D},
            {DUCK, KEY_S},
            {SHOOT, KEY_F}
    });
    player->assign<GravityComponent>();
    player->assign<SolidComponent>();
    player->assign<KineticComponent>(0.0f, 0.0f);
    player->assign<LuigiComponent>();
}

WorldBuilder& WorldBuilder::initPlayers(ECS::World*& world_, GameMap*& pMap_, bool secondPlayer) {
    Vector2 spawnPositionP1 = pMap_->getSpawnPositionP1();
    Vector2 spawnPositionP2 = pMap_->getSpawnPositionP2();
    if (!secondPlayer) {
        ECS::Entity* player = world_->create();
        if (GameConfig::getInstance().getCharacter() == Character::MARIO) {
            std::cout << "DEBUG: Creating Mario" << std::endl;
            initMarioPlayer(player, spawnPositionP1);
        } else {
            std::cout << "DEBUG: Creating Luigi" << std::endl;
            initLuigiPlayer(player, spawnPositionP1);
        }
        player->assign<LeadCameraComponent>();
    }
    else {
        ECS::Entity* mario = world_->create();
        initMarioPlayer(mario, spawnPositionP1);
        
        ECS::Entity* luigi = world_->create();
        initLuigiPlayer(luigi, spawnPositionP2);
    }
    return *this;
}

WorldBuilder& WorldBuilder::initCamera(ECS::World*& world_, const int& screenWidth_, const int& screenHeight_, size_t& cameraId_) {
    ECS::Entity* camera = world_->create();
    camera->assign<CameraComponent>(
            Vector2{screenWidth_ / 2.f,  screenHeight_ / 2.f},
            Vector2{screenWidth_ / 2.f,  screenHeight_ / 2.f},
            0.0f,
            1.0f
            );
    cameraId_ = camera->getEntityId();
    return *this;
}

WorldBuilder& WorldBuilder::initIdsMap(ECS::World*& world_, GameMap*& pMap_) {
    int mapWidth, mapHeight;
    mapWidth = pMap_->getWidth();
    mapHeight = pMap_->getHeight();
    auto staticEntitiesMap = world_->create();
    auto idsMapComponent = staticEntitiesMap->assign<IdsMapComponent>(mapWidth, mapHeight);
    staticEntitiesMap->assign<StaticEntitiesMapComponent>();

    // init static ids map
    for (ECS::Entity* object : world_->each<TileComponent, AABBComponent, SolidComponent>()) {
        auto aabb = object->get<AABBComponent>();

        if (round(aabb->collisionBox_.width) <= GAME_TILE_SIZE && round(aabb->collisionBox_.height) <= GAME_TILE_SIZE) {
            unsigned int x = (int)round(aabb->left() / 32);
            unsigned int y = (int)round(aabb->top() / 32);
            idsMapComponent->set(object->getEntityId(), x, y);
        } else {
            for (int j = (int)(round(aabb->top() / 32)); j < (int)(aabb->bottom() / 32); j++) {
                for (int i = (int)(round(aabb->left() / 32)); i < (int)(aabb->right() / 32); i++) {
                    idsMapComponent->set(object->getEntityId(), i, j);
                }
            }
        }
    }

    auto kineticEntitiesMap = world_->create();
    kineticEntitiesMap->assign<SpacialHashMapComponent>(mapWidth, mapHeight);
    kineticEntitiesMap->assign<KineticEntitiesMapComponent>();
    return *this;
}

WorldBuilder& WorldBuilder::initTextEntities(ECS::World*& world_, const int& screenWidth_) {
    auto coinCounterText = world_->create();
    coinCounterText->assign<TextComponent>(
            Text::Type::COIN_COUNTER,
            Vector2{20.0f, 20.0f},
            0);

    auto scoreCounterText = world_->create();
    scoreCounterText->assign<TextComponent>(
            Text::Type::SCORE_COUNTER,
            Vector2{screenWidth_ - 175.f, 20.0f},
            0);

    auto timerText = world_->create();
    timerText->assign<TextComponent>(
            Text::Type::TIMER,
            Vector2{screenWidth_ - 45.f, 20.0f},
            360);
    timerText->assign<TimerComponent>([&]() {}, 360, true); 

    world_->registerSystem(new TimerSystem());
    world_->registerSystem(new ScoreSystem());
    return *this;
}

WorldBuilder& WorldBuilder::startMusic(ECS::World*& world_) {
    world_->emit<SetMusicEvent>(SetMusicEvent(MusicId::SMB1_MAIN_THEME));
    return *this;
}

WorldBuilder& WorldBuilder::registerSystems(ECS::World*& world_,const int& screenWidth_, const int& screenHeight_,GameMap*& pMap_, ECS::EntitySystem*& animationSystem_, SoundSystem*& soundSystem_) {
        world_->registerSystem(new CameraSystem(
            screenWidth_,
            screenHeight_,
            pMap_->getPixelWidth(),
            pMap_->getPixelHeight()));
    world_->registerSystem(new PlayerSystem());
    world_->registerSystem(new EnemySystem());
    animationSystem_ = world_->registerSystem(new AnimationSystem());
    world_->registerSystem(new IdsMapSystem());
    world_->registerSystem(new PhysicSystem());
    world_->registerSystem(new TileSystem());
    //world_->registerSystem(new TimerSystem());
    world_->disableSystem(world_->registerSystem(new FlagSystem()));
    soundSystem_ = dynamic_cast<SoundSystem *>(world_->registerSystem(new SoundSystem()));
    return *this;
}
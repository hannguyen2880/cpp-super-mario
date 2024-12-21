#include "GameManager.h"
#include "GameConfig.h"

GameManager::GameManager(const char* mapName, const int screenWidth, const int screenHeight, bool secondPlayer)
    : mapName(mapName)
    , screenWidth_(screenWidth)
    , screenHeight_(screenHeight)
    , secondPlayer(secondPlayer)
    , previous(GetTime())
    , lag(0.0)
    , world_(nullptr)
    , pMap_(nullptr)
    , mapRenderer(nullptr)
    , textureRenderer(nullptr)
    , enemiesRenderer(nullptr)
    , objectRenderer(nullptr)
    , textRenderer_(nullptr)
{
    //Init();
}

GameManager::~GameManager() {
    cleanup();
}

void GameManager::Init() {
    run = true;
    pause = false;
    restart = false;

    world_ = ECS::World::createWorld();
    pMap_ = new GameMap(mapName);
    pMap_->loadMap(world_);
    
    mapRenderer = new MapRenderer(pMap_, SMB1_TILESET_PATH);
    textureRenderer = new TextureRenderer(SBM1_PLAYER_TILESET_PATH);
    enemiesRenderer = new EnemiesRenderer(SMB1_ENEMIES_TILESET_PATH);
    objectRenderer = new ObjectRenderer(SMB1_OBJECT_TILESET_PATH);
    textRenderer_ = new TextRenderer();

    initWorld();
    //SetTargetFPS(60);
}

void GameManager::Update() {
    if (!run || WindowShouldClose()) return;

    double current = GetTime();
    double elapsed = current - previous;
    previous = current;
    lag += elapsed;

    handleInput();

    while (lag >= MS_PER_UPDATE) {
        world_->tick(0.0f);
        lag -= MS_PER_UPDATE;
    }

    updateMusicStream();
}

void GameManager::Draw() {
    if (!run) return;
    ClearBackground(RAYWHITE);

    auto camera = world_->getById(cameraId_)->get<CameraComponent>();
    BeginMode2D(camera.get().camera);
    
    render(static_cast<float>(lag / MS_PER_UPDATE));
    
    EndMode2D();
    
    textRenderer_->render(world_);
    
}

void GameManager::cleanup() {
    if (world_) {
        world_->destroyWorld();
        delete world_;
        world_ = nullptr;
    }
    if (pMap_) {
        delete pMap_;
        pMap_ = nullptr;
    }
    if (mapRenderer) {
        delete mapRenderer;
        mapRenderer = nullptr;
    }
    if (textureRenderer) {
        delete textureRenderer;
        textureRenderer = nullptr;
    }
    if (enemiesRenderer) {
        delete enemiesRenderer;
        enemiesRenderer = nullptr;
    }
    if (objectRenderer) {
        delete objectRenderer;
        objectRenderer = nullptr;
    }
    if (textRenderer_) {
        delete textRenderer_;
        textRenderer_ = nullptr;
    }
}

bool GameManager::NeedsRestart() const {
    return restart;
}

void GameManager::restartGame() {
    auto player = world_->findFirst<PlayerComponent>();
    if (!player) {
        run = false;
        restart = true;
    }
}

void GameManager::initWorld() {

    initPlayers();

    // Init camera
    ECS::Entity* camera = world_->create();
    camera->assign<CameraComponent>(
            Vector2{screenWidth_ / 2.f,  screenHeight_ / 2.f},
            Vector2{screenWidth_ / 2.f,  screenHeight_ / 2.f},
            0.0f,
            1.0f
            );
    cameraId_ = camera->getEntityId();

    initIdsMap();
    registerSystems();
    initTextEntities();
    startMusic();
}

void GameManager::initMarioPlayer(ECS::Entity *player, Vector2 position) {
    player->getEntityId();
    player->assign<PlayerComponent>();
    player->assign<AABBComponent>(
            Rectangle {
                    position.x * 32,
                    position.y * 32,
                    32,
                    32});
    player->assign<TextureComponent>(MARIO_STAND);
    player->assign<LeadCameraComponent>();
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

void GameManager::initLuigiPlayer(ECS::Entity *player, Vector2 position) {
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

void GameManager::initPlayers() {
    Vector2 spawnPositionP1 = pMap_->getSpawnPositionP1();
    Vector2 spawnPositionP2 = pMap_->getSpawnPositionP2();
    ECS::Entity* mario = world_->create();
    initMarioPlayer(mario, spawnPositionP1);
    if (secondPlayer) {
        ECS::Entity* luigi = world_->create();
        initLuigiPlayer(luigi, spawnPositionP2);
    }
    // if (!secondPlayer) {
    //     ECS::Entity* player = world_->create();
    //     if (GameConfig::getInstance().getCharacter() == Character::MARIO) {
    //         std::cout << "DEBUG: Creating Mario" << std::endl;
    //         initMarioPlayer(player, spawnPositionP1);
    //     } else {
    //         std::cout << "DEBUG: Creating Luigi" << std::endl;
    //         initLuigiPlayer(player, spawnPositionP1);
    //     }
    // }
    // else {
    //     ECS::Entity* mario = world_->create();
    //     initMarioPlayer(mario, spawnPositionP1);
        
    //     ECS::Entity* luigi = world_->create();
    //     initLuigiPlayer(luigi, spawnPositionP2);
    // }
}

void GameManager::registerSystems() {
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
    world_->registerSystem(new TimerSystem());
    world_->disableSystem(world_->registerSystem(new FlagSystem()));
    soundSystem_ = dynamic_cast<SoundSystem *>(world_->registerSystem(new SoundSystem()));
}

void GameManager::handleInput() {
    for (auto ent : world_->each<CommandComponent>())
    {
        auto commandComponent = ent->get<CommandComponent>();
        auto playerComponent = ent->get<PlayerComponent>();

        if (IsKeyDown(KEY_RIGHT)) commandComponent->setCurrentCommand(KEY_RIGHT);
        else if (IsKeyDown(KEY_LEFT)) commandComponent->setCurrentCommand(KEY_LEFT);
        else if (IsKeyDown(KEY_DOWN)) commandComponent->setCurrentCommand(KEY_DOWN);
        else if (IsKeyDown(KEY_UP)) commandComponent->setCurrentCommand(KEY_UP);
        else if (IsKeyDown(KEY_W)) commandComponent->setCurrentCommand(KEY_W);
        else if (IsKeyDown(KEY_D)) commandComponent->setCurrentCommand(KEY_D);
        else if (IsKeyDown(KEY_A)) commandComponent->setCurrentCommand(KEY_A);
        else if (IsKeyDown(KEY_S)) commandComponent->setCurrentCommand(KEY_S);
        else if (IsKeyDown(KEY_Z)) commandComponent->setCurrentCommand(KEY_Z);
        else if (IsKeyDown(KEY_F)) commandComponent->setCurrentCommand(KEY_F);
        else commandComponent->setNullCommand();

        // make player sprint
        if (playerComponent) {
            if (ent->has<MarioComponent>()) {
                if (IsKeyDown(KEY_LEFT_SHIFT)) playerComponent->sprint = true;
                if (IsKeyUp(KEY_LEFT_SHIFT)) playerComponent->sprint = false;
            } else if (ent->has<LuigiComponent>()) {

            }
        }
    }

    // fixme: doesn't work properly
    // if (IsKeyReleased(KEY_ENTER)) restartGame();
}

void GameManager::initIdsMap() {
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
}

void GameManager::render(float d) {
    mapRenderer->renderBackground(world_);
    textureRenderer->renderTextureEntities(world_, d);
    textureRenderer->renderTileCollisionRect(world_);
    enemiesRenderer->renderUnderTileEnemies(world_, d);
    objectRenderer->render(world_);
    mapRenderer->render(world_, d);
    enemiesRenderer->renderOverTileEnemies(world_, d);
    textRenderer_->renderScoreTextComponents(world_);
}

void GameManager::initTextEntities() {
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

    world_->registerSystem(new ScoreSystem());
}

void GameManager::startMusic() {
    world_->emit<SetMusicEvent>(SetMusicEvent(MusicId::SMB1_MAIN_THEME));
}

void GameManager::updateMusicStream() {
    UpdateMusicStream(soundSystem_->getCurrentMusic());
}
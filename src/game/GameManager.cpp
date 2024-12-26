#include "GameManager.h"
#include "GameConfig.h"
#include "WorldBuilder.h"
#include <iostream>
#include <fstream>
#include <string>
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
    Init();
}

GameManager::~GameManager() {
    printScore();
    saveScore();
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
    objectRenderer = new ObjectRenderer(SMB1_OBJECT_TILESET_PATH);
    
    textureRenderer = new TextureRenderer(SBM1_PLAYER_TILESET_PATH);
    enemiesRenderer = new EnemiesRenderer(SMB1_ENEMIES_TILESET_PATH);
    textRenderer_ = new TextRenderer();
    //using tileset type to load the correct tileset
}

    initWorld();
    SetTargetFPS(60);
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
    delete pMap_;
    delete mapRenderer;
    delete textureRenderer;
    delete enemiesRenderer;
    delete objectRenderer;
    delete textRenderer_;
    pMap_ = nullptr;
    mapRenderer = nullptr;
    textureRenderer = nullptr;
    enemiesRenderer = nullptr;
    objectRenderer = nullptr;
    textRenderer_ = nullptr;
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
  WorldBuilder worldBuilder;
    worldBuilder.initPlayers(world_, pMap_, secondPlayer)
                .initCamera(world_, screenWidth_, screenHeight_, cameraId_)
                .initIdsMap(world_, pMap_)
                .registerSystems(world_, screenWidth_, screenHeight_, pMap_, animationSystem_, soundSystem_)
                .initTextEntities(world_, screenWidth_)
                .startMusic(world_);
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
void GameManager::render(float d) {
    printScore();
    mapRenderer->renderBackground(world_);
    mapRenderer->renderDecoration(world_);
    textureRenderer->renderTextureEntities(world_, d);
    textureRenderer->renderTileCollisionRect(world_);
    enemiesRenderer->renderUnderTileEnemies(world_, d);
    objectRenderer->render(world_);
    mapRenderer->render(world_, d);
    enemiesRenderer->renderOverTileEnemies(world_, d);
    textRenderer_->renderScoreTextComponents(world_);
}


void GameManager::updateMusicStream() {
    UpdateMusicStream(soundSystem_->getCurrentMusic());
}

void GameManager::saveScore() {

    std::ofstream fileOut;
    const char* filePath = "score.txt";
    //append score to file, then the endline character
    fileOut.open(filePath);
    if (!fileOut.is_open()) {
         throw std::runtime_error("Could not open file for writing");
    }
        for (auto ent : this->world_->each<TextComponent>()) {
        auto textComponent = ent->get<TextComponent>();

        switch (textComponent->type) {
            case Text::Type::SCORE_COUNTER:
                fileOut << textComponent->getValue() << std::endl;
                break;
            default:
                break;
        }
        fileOut.close();
}
}

void GameManager::printScore() {
    for (auto ent : this->world_->each<TextComponent>()) {
        auto textComponent = ent->get<TextComponent>();

        switch (textComponent->type) {
            case Text::Type::SCORE_COUNTER:
                std::cout << "Score: " << textComponent->getValue() << std::endl;
                break;
            default:
                break;
        }
    }
}
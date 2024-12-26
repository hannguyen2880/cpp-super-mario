#pragma once

#include <cmath>
#include <iostream>
#include <string>
#include <set>
#include <stdexcept>

#include <raylib.h>
#include <tmxlite/Map.hpp>
#include <tmxlite/Layer.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/ObjectGroup.hpp>

#include "ECS.h"
#include "../Constants.h"
#include "../components/Components.h"


class GameMap {
private:
    void loadMapBasicInfo(const tmx::Vector2u& orientation);

    void loadProperties(std::vector<tmx::Property> properties);

    void loadMapTiles(const std::vector<tmx::Tileset>& tilesets, const std::set<unsigned int>& usedTiles);

    std::set<unsigned int> loadLayers(const std::vector<tmx::Layer::Ptr>& layers, ECS::World* world);

    Texture2D getTexture(const std::string& path, tmx::Vector2u tilePosition, tmx::Vector2u tileSize);

    void loadTileEntity(ECS::Entity* ent, tmx::FloatRect AABB, std::vector<tmx::Property> properties, std::string layerName);

    void createEnemy(ECS::Entity *ent, std::vector<tmx::Property> properties);

    void setEnemyType(ECS::Entity *ent, std::string type);

    void createPiranhaPlant(ECS::World* world, float spawnX, float spawnY);

    ECS::Entity * createParachute(ECS::Entity* entity);

    void createObject(ECS::Entity *entity, std::vector<tmx::Property> properties);
    
    void createEscalator(ECS::World* world, ECS::Entity* ent);
    

    std::string name;
    int height_;
    int width_;
    bool loaded_;
    unsigned int** graphicsLayer_;
    unsigned int** decorationLayer_;
    Vector2 spawnPositionP1_;
    Vector2 spawnPositionP2_;
    std::map<unsigned int, TileTexture> mapTextureTable_;

public:
    GameMap(std::string filename);

    virtual ~GameMap();

    void loadMap(ECS::World* world);

    bool isMapLoaded();

    int getHeight() const;

    int getWidth() const;

    int getPixelHeight() const;

    int getPixelWidth() const;

    const Vector2 &getSpawnPositionP1() const;

    const Vector2 &getSpawnPositionP2() const;

    void unloadTextures();

    unsigned int **getGraphicsLayer() const;

    unsigned int **getDecorationLayer() const;

    const std::map<unsigned int, TileTexture> &getTextureTable() const;

    Texture2D getTexture(unsigned int id);

};



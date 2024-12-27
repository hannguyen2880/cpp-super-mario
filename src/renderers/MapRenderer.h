/**
 * @startuml
 * class Renderer {
 * }
 * 
 * class GameMap {
 * }
 * 
 * class MapRenderer extends Renderer {
 *     +MapRenderer(GameMap *map, const char* filepath)
 *     +void render(ECS::World* world, float delta)
 *     +virtual ~MapRenderer()
 *     +void renderBackground(ECS::World *world)
 *     -void drawGraphicsLayer(unsigned int** mapToRender, ECS::World* world, bool graphics)
 *     -void renderTexture(TextureId textureId, int x, int y)
 *     -void renderOtherEntities(ECS::World *pWorld, float d)
 *     -GameMap map_
 * }
 * 
 * MapRenderer *-- GameMap : composes
 * @enduml
 */

#pragma once

#include <raylib.h>
#include "../map/GameMap.h"
#include "ECS.h"
#include "Renderer.h"

class MapRenderer : public Renderer {
public:

    MapRenderer(GameMap *map, const char* filepath1, int background);

    void render(ECS::World* world, float delta);

    virtual ~MapRenderer();

    void renderBackground(ECS::World *world, int background);

    void renderDecoration(ECS::World* world);

    void loadBackgroundTextures();

private:

    void drawGraphicsLayer(unsigned int** mapToRender, ECS::World* world, bool graphics);

    void renderTexture(TextureId textureId, int x, int y);

    void renderOtherEntities(ECS::World *pWorld, float d);

private:
    GameMap map_;
    std::unordered_map<std::string, Texture2D> backgroundtextures_;
    int background;
};



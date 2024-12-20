#ifndef MARIO_MAKER_MAPRENDERER_H
#define MARIO_MAKER_MAPRENDERER_H
#include <raylib.h>
#include "../map/GameMap.h"
#include "ECS.h"
#include "Renderer.h"

class MapRenderer : public Renderer {
public:

    MapRenderer(GameMap *map, const char* filepath1);

    void render(ECS::World* world, float delta);

    virtual ~MapRenderer();

    void renderBackground(ECS::World *world);
    void renderDecoration(ECS::World* world);

    void loadBackgroundTextures();
private:

    void drawGraphicsLayer(unsigned int** mapToRender, ECS::World* world, bool graphics);
    void renderTexture(TextureId textureId, int x, int y);
    void renderOtherEntities(ECS::World *pWorld, float d);

private:
    GameMap map_;
    std::unordered_map<std::string, Texture2D> backgroundtextures_;
};


#endif //MARIO_MAKER_MAPRENDERER_H

#pragma once
#include "../renderers/MapRenderer.h"
#include "../renderers/ObjectRenderer.h"
#include "../renderers/TextureRenderer.h"
#include "../renderers/EnemiesRenderer.h"
#include "../renderers/TextRenderer.h"
#include "../map/GameMap.h"

class RendererFactory {
public:
    static MapRenderer* createMapRenderer(GameMap* pMap, const char* tilesetPath, int background);

    static ObjectRenderer* createObjectRenderer(const char* tilesetPath);

    static TextureRenderer* createTextureRenderer(const char* tilesetPath);

    static EnemiesRenderer* createEnemiesRenderer(const char* tilesetPath);

    static TextRenderer* createTextRenderer();
};

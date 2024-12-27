#include "RendererFactory.h"

MapRenderer* RendererFactory::createMapRenderer(GameMap* pMap, const char* tilesetPath, int background) {
        return new MapRenderer(pMap, tilesetPath, background);
}

ObjectRenderer* RendererFactory::createObjectRenderer(const char* tilesetPath) {
        return new ObjectRenderer(tilesetPath);
}

TextureRenderer* RendererFactory::createTextureRenderer(const char* tilesetPath) {
        return new TextureRenderer(tilesetPath);
}

EnemiesRenderer* RendererFactory::createEnemiesRenderer(const char* tilesetPath) {
        return new EnemiesRenderer(tilesetPath);
}

TextRenderer* RendererFactory::createTextRenderer() {
        return new TextRenderer();
}
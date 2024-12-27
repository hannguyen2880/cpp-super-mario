#pragma once

#include <unordered_map>
#include <raylib.h>
#include "ECS.h"
#include "Renderer.h"
#include "TextureId.h"

class TextureRenderer : public Renderer {
public:

    explicit TextureRenderer(const char* filepath);

    ~TextureRenderer();

    void renderTexture(TextureId textureId, Rectangle dstRect, bool flipH = false, bool flipV = false);

    void renderTextureEntities(ECS::World* world, float delta);

    void renderTileCollisionRect(ECS::World* world);

    std::unordered_map<TextureId, Texture2D>::iterator returnTexturesIt();

private:

    void renderEntity(ECS::Entity *entity, float d);
    
};


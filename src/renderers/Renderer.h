#pragma once
#include <raylib.h>
#include "TextureId.h"
#include "../Constants.h"
#include <unordered_map>

class Renderer {
public:

    Renderer(const char* filepath);

    char* getFilePath();
    
    virtual void cleanup();

protected:

    void loadTextures();

    Texture2D loadTexture(TextureId textureId, float width, float height);

    void renderEntityTexture(TextureId textureId, Rectangle dstRect, bool flipH, bool flipV);

    void render2XEntityTexture(TextureId textureId, Rectangle dstRect, bool flipH, bool flipV);

private:

    std::pair<int, int> getTextureDimensions(TextureId textureId, int width, int height);
    
protected:
    std::unordered_map<TextureId, Rectangle*> texturePositions_{};
    std::unordered_map<TextureId, Texture2D> textures_{};

private:
    const char* filepath_;
};


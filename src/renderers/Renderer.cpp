#include "Renderer.h"

Renderer::Renderer(const char* filepath) : filepath_(filepath) {};

char* Renderer::getFilePath() {
        return const_cast<char *>(filepath_);
}

void Renderer::cleanup() {
        for (auto& texture : textures_) {
            UnloadTexture(texture.second);
        }
        textures_.clear();
        texturePositions_.clear();
}

void Renderer::loadTextures() {
        auto it = texturePositions_.begin();

        for (; it != texturePositions_.end(); it++)
        {
            auto rect = it->second;
            float width = rect->width, height = rect->height;
            textures_.insert({it->first, loadTexture(it->first, width, height)});
        }
}

Texture2D Renderer::loadTexture(TextureId textureId, float width, float height) {
        auto it = texturePositions_.find(textureId);

        Rectangle rectangle = *it->second;
        std::pair<int, int> newDims = getTextureDimensions(textureId, (int) width, (int) height);

        Image image = LoadImage(filepath_);
        ImageCrop(&image, rectangle);
        ImageResize(&image, newDims.first, newDims.second);

        Texture2D texture2D = LoadTextureFromImage(image);
        UnloadImage(image);

        return texture2D;
}

void Renderer::renderEntityTexture(TextureId textureId, Rectangle dstRect, bool flipH, bool flipV) {
        auto it = textures_.find(textureId);
        auto it1 = texturePositions_.find(textureId);
        if (it != textures_.end())
        {
            if (dstRect.width == 0) dstRect.width = it1->second->width;
            if (dstRect.height == 0) dstRect.height = it1->second->height;
            Texture2D texture2D = it->second;
            DrawTextureRec(texture2D,
                           Rectangle{0, 0, (flipH ? -1 : 1) * dstRect.width, (flipV ? -1 : 1) * dstRect.height } ,
                           Vector2{dstRect.x, dstRect.y},
                           WHITE);
        }
}

void Renderer::render2XEntityTexture(TextureId textureId, Rectangle dstRect, bool flipH, bool flipV) {
        auto it = textures_.find(textureId);
        auto it1 = texturePositions_.find(textureId);
        if (it != textures_.end())
        {
            if (dstRect.width == 0) dstRect.width = it1->second->width;
            if (dstRect.height == 0) dstRect.height = it1->second->height;
            Texture2D texture2D = it->second;
            Rectangle sourceRect = {
                    0.0f,
                    0.0f,
                    (flipH ? -1.0f : 1.0f) * dstRect.width / 2,
                    (flipV ? -1.0f : 1.0f) * dstRect.height / 2 };
            Rectangle destRect = { dstRect.x, dstRect.y, dstRect.width, dstRect.height };
            Vector2 origin = { 0.0f, 0.0f };

            DrawTexturePro(
                    texture2D,
                    sourceRect,
                    destRect,
                    origin,
                    0.0f,
                    WHITE );
        }
}


std::pair<int, int> Renderer::getTextureDimensions(TextureId textureId, int width, int height) {
        std::pair<int, int> dims;

        switch (textureId) {
            case MARIO_MEGA_DEAD:  case MARIO_MEGA_DRIFT:  case MARIO_MEGA_DUCK:
            case MARIO_MEGA_JUMP:  case MARIO_MEGA_RUN_1:  case MARIO_MEGA_RUN_2:
            case MARIO_MEGA_RUN_3: case MARIO_MEGA_STAND:  case MARIO_MEGA_SIT_1:
            case MARIO_MEGA_SIT_2: case LUIGI_MEGA_STAND:  case LUIGI_MEGA_DUCK:
            case LUIGI_MEGA_JUMP:  case LUIGI_MEGA_DRIFT:  case LUIGI_MEGA_RUN_1:
            case LUIGI_MEGA_RUN_2: case LUIGI_MEGA_RUN_3:  case LUIGI_MEGA_DEAD:
            case LUIGI_MEGA_SIT_1: case LUIGI_MEGA_SIT_2:  case MARIO_MEGA_GREET:
                dims.first = width * 4;
                dims.second = height * 4;
                break;
            default:
                dims.first = width * 2;
                dims.second = height * 2;
                break;
        }

        return dims;
}
    
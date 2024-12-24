#include "../Constants.h"
#include "MapRenderer.h"

MapRenderer::~MapRenderer() {
    map_.unloadTextures();
    for (auto& texture : backgroundtextures_) {
        UnloadTexture(texture.second);
    }
}

MapRenderer::MapRenderer(GameMap *map, const char* filepath1)
:map_(*map), Renderer(filepath1)
{
    texturePositions_.insert({QUESTION_BLOCK_1, new Rectangle{368, 0, TILE_SIZE, TILE_SIZE}});
    texturePositions_.insert({QUESTION_BLOCK_2, new Rectangle{384, 0, TILE_SIZE, TILE_SIZE}});
    texturePositions_.insert({QUESTION_BLOCK_3, new Rectangle{400, 0, TILE_SIZE, TILE_SIZE}});
    texturePositions_.insert({QUESTION_BLOCK_OFF, new Rectangle{416, 0, TILE_SIZE, TILE_SIZE}});

    texturePositions_.insert({BRICK, new Rectangle{32, 0, TILE_SIZE, TILE_SIZE}});
    texturePositions_.insert({SQUARE_BRICK, new Rectangle{0, 16, TILE_SIZE, TILE_SIZE}});
    texturePositions_.insert({BRICK_DEBRIS_1, new Rectangle{32, 0,
                                                                (int) (TILE_SIZE / 2),
                                                                (int) (TILE_SIZE / 2)}});
    texturePositions_.insert({BRICK_DEBRIS_2, new Rectangle{40, 0,
                                                            (int) (TILE_SIZE / 2),
                                                            (int) (TILE_SIZE / 2)}});
    texturePositions_.insert({BRICK_DEBRIS_3, new Rectangle{32, 8,
                                                            (int) (TILE_SIZE / 2),
                                                            (int) (TILE_SIZE / 2)}});
    texturePositions_.insert({BRICK_DEBRIS_4, new Rectangle{40, 8,
                                                            (int) (TILE_SIZE / 2),
                                                            (int) (TILE_SIZE / 2)}});

    texturePositions_.insert({COIN_1, new Rectangle{368, 16, TILE_SIZE, TILE_SIZE}});
    texturePositions_.insert({COIN_2, new Rectangle{384, 16, TILE_SIZE, TILE_SIZE}});
    texturePositions_.insert({COIN_3, new Rectangle{400, 16, TILE_SIZE, TILE_SIZE}});

    texturePositions_.insert({BLACK_CANNON, new Rectangle{144, 0, TILE_SIZE, TILE_SIZE * 2}});

    //Render escalator
    texturePositions_.insert({ESCALATOR_1, new Rectangle{48, 16, TILE_SIZE, TILE_SIZE / 2}});
    //std::cout << "Escalator 1" << escalator_origin->x << " " << escalator_origin->y << " " << escalator_origin->width << " " << escalator_origin->height << std::endl <<std::endl;
    texturePositions_.insert({ESCALATOR_2, new Rectangle{48, 16, TILE_SIZE, TILE_SIZE / 2}});
    texturePositions_.insert({ESCALATOR_3, new Rectangle{48, 16, TILE_SIZE, TILE_SIZE / 2}});
    
    loadTextures();

    std::cout << "MapRenderer created" << std::endl << std::endl;
    //createCombinedEscalatorTexture();
}

void MapRenderer::render(ECS::World* world, float delta) {
    drawGraphicsLayer(map_.getGraphicsLayer(), world, true);
    renderOtherEntities(world, delta);
}

void MapRenderer::loadBackgroundTextures() {
    backgroundtextures_[AUTUMN] = LoadTexture(AUTUMN);
    // backgroundtextures_[LANDSCAPE2] = LoadTexture(LANDSCAPE2.c_str());
    // backgroundtextures_[LANDSCAPE3] = LoadTexture(LANDSCAPE3.c_str());
}

void MapRenderer::renderBackground(ECS::World* world) {
    // Ensure textures are loaded
    if (backgroundtextures_.empty()) {
        loadBackgroundTextures();
    }

    // Draw the textures (example: drawing the first texture)
    DrawTexture(backgroundtextures_[AUTUMN], 0, 0, WHITE);
    // You can add logic to draw other textures as needed
}

void MapRenderer::renderDecoration(ECS::World* world) {
    drawGraphicsLayer(map_.getDecorationLayer(), world, false);
}

void MapRenderer::drawGraphicsLayer(unsigned int **mapToRender, ECS::World* world, bool graphics) {

    auto objectMapComponent = world->findFirst<IdsMapComponent>();

    for (int i = 0; i < map_.getWidth(); i++)
    {
        for (int j = 0; j < map_.getHeight(); j++)
        {
            unsigned int id = mapToRender[i][j];
            if (id != 0)
            {
                Texture2D texture2D = map_.getTexture(id);
                if (!graphics)
                {
                    DrawTexture(texture2D, i * 32, j * 32, WHITE);
                } else {
                    auto map = objectMapComponent->get<IdsMapComponent>();
                    int id = map->get(i, j);
                    auto ent = world->getById(id);

                    if (!ent) continue;
                    if (!ent->has<AABBComponent, SolidComponent, TileComponent>()) continue;

                    if (ent->has<TextureComponent>()) {
                        auto aabb = ent->get<AABBComponent>();
                        auto textureComponent = ent->get<TextureComponent>();

                        renderTexture(textureComponent->textureId_, (int) aabb->left(), (int) aabb->top());
                    } else {
                        DrawTexture(texture2D, i * 32, j * 32, WHITE);
                    }
                }
            }
        }
    }
}

void MapRenderer::renderTexture(TextureId textureId, int x, int y) {
    auto it = textures_.find(textureId);
    if (it != textures_.end())
    {
        Texture2D texture2D = it->second;
        DrawTexture(texture2D, x, y, WHITE);
    }
}

void MapRenderer::renderOtherEntities(ECS::World *pWorld, float d) {
    for (auto ent : pWorld->each<TextureComponent, TileComponent, AABBComponent>()) {
        auto aabb = ent->get<AABBComponent>();
        auto textureComponent = ent->get<TextureComponent>();
        auto kinetic = ent->get<KineticComponent>();

        if (kinetic) {
            Rectangle rect{
                    aabb->left() + textureComponent->offSetX - kinetic->speedX_ * d,
                    aabb->top() + textureComponent->offSetY - kinetic->speedY_ * d,
                    textureComponent->w > 0 ? textureComponent->w : aabb->collisionBox_.width,
                    textureComponent->h > 0 ? textureComponent->h : aabb->collisionBox_.height
            };

            Renderer::renderEntityTexture(
                    textureComponent->textureId_,
                    rect,
                    textureComponent->flipH,
                    textureComponent->flipV);
        } else {
            renderTexture(textureComponent->textureId_, (int) aabb->left(), (int) aabb->top());
        }
    }
}

Texture2D MapRenderer::createCombinedEscalatorTexture() {

     // Assuming the textures are already loaded and stored in texturePositions_
    Rectangle* escalator1 = texturePositions_[ESCALATOR_1];
    Rectangle* escalator2 = texturePositions_[ESCALATOR_2];
    Rectangle* escalator3 = texturePositions_[ESCALATOR_3];

    // Calculate the width and height of the combined texture
    int combinedWidth = escalator1->width + escalator2->width + escalator3->width;
    int combinedHeight = escalator1->height; 

    // Create a render texture to draw the combined texture
    RenderTexture2D combinedTexture = LoadRenderTexture(combinedWidth, combinedHeight);

    // Start drawing to the render texture
    BeginTextureMode(combinedTexture);
    ClearBackground(BLANK);

    // Draw each escalator texture side by side
    DrawTextureRec(map_.getTexture(ESCALATOR_1), *escalator1, {0, 0}, WHITE);
    DrawTextureRec(map_.getTexture(ESCALATOR_2), *escalator2, {escalator1->width, 0}, WHITE);
    DrawTextureRec(map_.getTexture(ESCALATOR_3), *escalator3, {escalator1->width + escalator2->width, 0}, WHITE);

    // End drawing to the render texture
    EndTextureMode();

    // Create a new Rectangle for the combined texture
    Rectangle* combinedEscalator = new Rectangle{0, 0, combinedWidth, combinedHeight};

    // Insert the combined texture into the texturePositions_ map
    texturePositions_.insert({ESCALATOR, combinedEscalator});

    // Return the combined texture
    return combinedTexture.texture;
}
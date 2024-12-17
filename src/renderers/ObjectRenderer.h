#ifndef MARIO_MAKER_OBJECTRENDERER_H
#define MARIO_MAKER_OBJECTRENDERER_H
#include "Renderer.h"
#include "TextureId.h"
#include "../components/Components.h"
#include "ECS.h"

class ObjectRenderer : public Renderer {
public:

    explicit ObjectRenderer(const char* filepath);

    ~ObjectRenderer();

    void render(ECS::World* world);

};


#endif //MARIO_MAKER_OBJECTRENDERER_H

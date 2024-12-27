#pragma once 

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



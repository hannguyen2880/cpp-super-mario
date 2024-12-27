#pragma once

#include "../components/Components.h"
#include "ECS.h"
#include "Renderer.h"
#include "TextureId.h"

class ObjectRenderer : public Renderer {
public:
  explicit ObjectRenderer(const char *filepath);

  ~ObjectRenderer();

  void render(ECS::World *world);
};

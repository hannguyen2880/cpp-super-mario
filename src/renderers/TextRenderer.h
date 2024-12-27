/**
 * @startuml
 * class TextRenderer {
 *     +TextRenderer()
 *     +~TextRenderer()
 *     +void render(ECS::World* world)
 *     +void renderScoreTextComponents(ECS::World *world)
 *     -Font textFont
 * }
 * @enduml
 */

#ifndef MARIO_MAKER_TEXTRENDERER_H
#define MARIO_MAKER_TEXTRENDERER_H
#include "../components/Components.h"
#include "ECS.h"
#include <raylib.h>

class TextRenderer {
public:
  TextRenderer();

  ~TextRenderer();

  void render(ECS::World *world);

  void renderScoreTextComponents(ECS::World *world);

private:
  Font textFont;
};

#endif // MARIO_MAKER_TEXTRENDERER_H

#pragma once
#include <raylib.h>
#include "ECS.h"
#include "../components/Components.h"
#include <chrono>

class TextRenderer {
public:

    TextRenderer();

    ~TextRenderer();

    void render(ECS::World* world);

    void renderScoreTextComponents(ECS::World *world);

    void renderTimerTextComponents(ECS::World *world);

private:
    Font textFont;
};

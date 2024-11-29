#pragma once
#include "raylib.h"

class Screen {
public:
    virtual void Init() = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0;
    virtual void Unload() = 0;
    virtual ~Screen() = default;
};
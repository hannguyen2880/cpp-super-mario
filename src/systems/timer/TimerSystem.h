#pragma once 

#include "ECS.h"
#include "components/Components.h"

using namespace ECS;

class TimerSystem : public EntitySystem {
public:

    TimerSystem();

    ~TimerSystem() override;

    void tick(World* world, float delta);

    void configure(World* world) override;

    void unconfigure(World* world) override;

};



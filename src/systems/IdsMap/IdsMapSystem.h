#ifndef MARIO_MAKER_IDSMAPSYSTEM_H
#define MARIO_MAKER_IDSMAPSYSTEM_H
#include "ECS.h"
#include <cmath>
#include "components/Components.h"
using namespace ECS;

class IdsMapSystem : public EntitySystem {
public:
    IdsMapSystem();

    ~IdsMapSystem();

    void configure(World *world) override;

    void unconfigure(World *world) override;

    void tick(World *world, ECS::DefaultTickData data) override;
};


#endif //MARIO_MAKER_IDSMAPSYSTEM_H

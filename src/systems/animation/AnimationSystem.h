/**
 * @startuml
 * class ECS::EntitySystem {
 *     +void configure(ECS::World* world)
 *     +void unconfigure(ECS::World* world)
 *     +void tick(ECS::World* world, float delta)
 * }
 * 
 * class IdsMapSystem extends ECS::EntitySystem {
 *     +IdsMapSystem()
 *     +~IdsMapSystem()
 *     +void configure(ECS::World* world) <<override>>
 *     +void unconfigure(ECS::World* world) <<override>>
 *     +void tick(ECS::World* world, ECS::DefaultTickData data) <<override>>
 * }
 * @enduml
 */

#ifndef MARIO_MAKER_ANIMATIONSYSTEM_H
#define MARIO_MAKER_ANIMATIONSYSTEM_H
#include "ECS.h"
#include "components/Components.h"

using namespace ECS;

class AnimationSystem : public EntitySystem {
public:

    AnimationSystem();

    void tick(World* world, float delta) override;

    void configure(World* world) override;

    virtual ~AnimationSystem();

    void unconfigure(World* world) override;

};


#endif //MARIO_MAKER_ANIMATIONSYSTEM_H

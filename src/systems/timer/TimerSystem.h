/**
 * @startuml
 * class TimerSystem {
 *     +TimerSystem()
 *     +~TimerSystem() <<override>>
 *     +void tick(World* world, float delta)
 *     +void configure(World* world) <<override>>
 *     +void unconfigure(World* world) <<override>>
 * }
 * 
 * TimerSystem <|-- EntitySystem
 * @enduml
 */

#ifndef MARIO_MAKER_TIMERSYSTEM_H
#define MARIO_MAKER_TIMERSYSTEM_H
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


#endif //MARIO_MAKER_TIMERSYSTEM_H

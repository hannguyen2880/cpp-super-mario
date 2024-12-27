/**
 * @startuml
 * class EntitySystem {
 *     + void configure(World *world) <<abstract>>
 *     + void unconfigure(World *world) <<abstract>>
 *     + void tick(World *world, ECS::DefaultTickData data) <<abstract>>
 * }
 * 
 * class EventSubscriber {
 *     + void receive(World *world, const Event &event) <<abstract>>
 * }
 * 
 * class CollisionWithFinalPoleEvent {
 * }
 * 
 * class FlagSystem extends EntitySystem {
 *     + FlagSystem()
 *     + ~FlagSystem()
 *     + void configure(World *world) <<override>>
 *     + void unconfigure(World *world) <<override>>
 *     + void tick(World *world, ECS::DefaultTickData data) <<override>>
 *     + void receive(World *world, const CollisionWithFinalPoleEvent &event) <<override>>
 * }
 * 
 * FlagSystem "1" *-- "1" ECS::Entity
 * FlagSystem <|.. EventSubscriber : implements
 * EventSubscriber <|.. CollisionWithFinalPoleEvent
 * @enduml
 */

#ifndef MARIO_MAKER_FLAGSYSTEM_H
#define MARIO_MAKER_FLAGSYSTEM_H
#include "ECS.h"
#include "events/Events.h"
#include "components/Components.h"

using namespace ECS;

enum FlagState {
    NONE,
    TAKING_FLAG_DOWN,
    WALKING_TO_CASTE
};

class FlagSystem : public EntitySystem,
                   public EventSubscriber<CollisionWithFinalPoleEvent> {
public:
    FlagSystem();

    ~FlagSystem();

    void tick(World* world, float delta) override;

    void configure(World* world) override;

    void unconfigure(World* world) override;

    void receive(World* world, const CollisionWithFinalPoleEvent& collisionWithFinalPole) override;

private:
    Entity* winner_;
    FlagState state_ = NONE;
    Entity* winningFlag_;
    float flagPoleBottom_;
    Entity *finalPole_;
};

#endif //MARIO_MAKER_FLAGSYSTEM_H

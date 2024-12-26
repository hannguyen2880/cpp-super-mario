/**
 * @startuml
 * class ECS::EntitySystem {
 *     +void configure(ECS::World* world)
 *     +void unconfigure(ECS::World* world)
 *     +void tick(ECS::World* world, float delta)
 * }
 * 
 * class ECS::EventSubscriber {
 * }
 * 
 * class KillEnemyEvent {
 * }
 * 
 * class EnemyCollectableCollisionEvent {
 * }
 * 
 * class EnemySystem extends ECS::EventSubscriber {
 *     +EnemySystem()
 *     +void configure(World* world) <<override>>
 *     +void unconfigure(World* world) <<override>>
 *     +void tick(World* world, float delta) <<override>>
 *     +void receive(World* world, const Event& event) <<override>>
 *     +~EnemySystem()
 * }
 * 
 * EnemySystem *-- KillEnemyEvent : composes
 * EnemySystem *-- EnemyCollectableCollisionEvent : composes
 * @enduml
 */

#ifndef MARIO_MAKER_ENEMYSYSTEM_H
#define MARIO_MAKER_ENEMYSYSTEM_H
#include "ECS.h"
#include "events/Events.h"
#include "components/Components.h"

using namespace ECS;

class EnemySystem :
        public EntitySystem,
        public EventSubscriber<KillEnemyEvent>,
        public EventSubscriber<EnemyCollectableCollisionEvent> {
public:
    EnemySystem();

    ~EnemySystem() override;

    void tick(World* world, float delta) override;

    void configure(World* world) override;

    void unconfigure(World* world) override;

    void receive(World* world, const KillEnemyEvent& killEnemyEvent) override;

    void receive(World* world, const EnemyCollectableCollisionEvent& event) override;

private:

    void manageEnemyEntities(World* world);

    void killEnemyWithFireball(Entity *entity);

    void killEnemyWithJump(Entity *entity);

    void managePiranhaPlants(World* world);

    void manageTartossos(World *world);

    void manageParachutes(World *world);

    void createChildGoombas(World *world, Rectangle sourceRect, bool b);

    void eatMushroom(Entity *entity, Collectible::Type type);

    void manageThwomps(World *world);
};


#endif //MARIO_MAKER_ENEMYSYSTEM_H

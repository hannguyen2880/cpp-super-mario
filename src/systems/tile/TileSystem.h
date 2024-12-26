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
 * class BreakEvent {
 * }
 * 
 * class TileSystem extends EntitySystem {
 *     + TileSystem()
 *     + ~TileSystem()
 *     + void configure(World *world) <<override>>
 *     + void unconfigure(World *world) <<override>>
 *     + void tick(World *world, ECS::DefaultTickData data) <<override>>
 *     + void receive(World *world, const BreakEvent &event) <<override>>
 * }
 * 
 * TileSystem "1" *-- "1" ECS::Entity
 * TileSystem <|.. EventSubscriber : implements
 * EventSubscriber <|.. BreakEvent
 * @enduml
 */
#ifndef MARIO_MAKER_TILESYSTEM_H
#define MARIO_MAKER_TILESYSTEM_H
#include "ECS.h"
#include "events/Events.h"
#include "components/Components.h"
#include "Constants.h"

using namespace ECS;

class TileSystem : public EntitySystem,
                    public EventSubscriber<BreakEvent> {
public:

    TileSystem();

    ~TileSystem();

    void tick(World* world, float delta);

    void configure(World* world) override;

    void unconfigure(World* world) override;

private:

    void createCoin(World *world, Entity *ent);

    void spawnSuperMarioMushroom(World *world, Entity *ent);

    void spawnMegaMushroom(World *world, Entity *ent);

    void spawnFlameMushroom(World *world, Entity *ent);

    void spawnOneUpMushroom(World *world, Entity *ent);

    void manageGrowComponents(World *world);

    void removeCollisionComponents(World* world);

    void manageBounceComponents(World* world);

    void createDebris(World *world, float xf, float yf);

    virtual void receive(World* world, const BreakEvent& breakEvent) override;

    void manageCannons(World *world);

    void spawnEntityFromCannon(World *world, Enemy::BulletType type, Rectangle rectangle, bool b);
};


#endif //MARIO_MAKER_TILESYSTEM_H

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
 * class EnemyCollisionEvent {
 * }
 * 
 * class PlayerCollectableCollisionEvent {
 * }
 * 
 * class PlayerSystem extends EntitySystem {
 *     + PlayerSystem()
 *     + ~PlayerSystem()
 *     + void configure(World *world) <<override>>
 *     + void unconfigure(World *world) <<override>>
 *     + void tick(World *world, ECS::DefaultTickData data) <<override>>
 *     + void receive(World *world, const EnemyCollisionEvent &event) <<override>>
 *     + void receive(World *world, const PlayerCollectableCollisionEvent &event) <<override>>
 * }
 * 
 * PlayerSystem "1" *-- "1" ECS::Entity
 * PlayerSystem <|.. EventSubscriber : implements
 * EventSubscriber <|.. EnemyCollisionEvent
 * EventSubscriber <|.. PlayerCollectableCollisionEvent
 * @enduml
 */

#ifndef MARIO_MAKER_PLAYERSYSTEM_H
#define MARIO_MAKER_PLAYERSYSTEM_H
#include "ECS.h"
#include "events/Events.h"
#include <raylib.h>

using namespace ECS;

class PlayerSystem :
        public EntitySystem,
        public EventSubscriber<EnemyCollisionEvent>,
        public EventSubscriber<PLayerCollectableCollisionEvent>{
public:
    PlayerSystem();

    void configure(World* world) override;

    void unconfigure(World* world) override;

    void tick(World* world, float delta) override;

    void setAnimation(Entity* playerEntity, PlayerState state);

    void receive(World* world, const EnemyCollisionEvent& enemyCollisionEvent) override;

    void receive(World* world, const PLayerCollectableCollisionEvent& pLayerCollectableCollisionEvent) override;
private:

    void eatMushroom(Entity *pEntity, Collectible::Type type);

    void handleFrozenTransform(Entity* entity);

    TextureId getRightTransitionAnimation(Entity* entity, Collectible::Type mushroom, bool isMario);

    bool isSuperTexture(TextureId textureId);

    bool isFlameTexture(TextureId textureId);

    bool isMegaTexture(TextureId textureId);

    void movePlayer(Entity* player);

    void shrink(Entity *player);

    void createFireBullet(World *world, Entity *entity);
};


#endif //MARIO_MAKER_PLAYERSYSTEM_H

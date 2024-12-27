/**
 * @startuml
 * class PhysicSystem {
 *     +PhysicSystem()
 *     +void tick(World* world, float delta) <<override>>
 *     +void configure(World* world) <<override>>
 *     +void unconfigure(World* world) <<override>>
 *     +virtual ~PhysicSystem()
 *     -void checkXEnemyCollision(Entity *ent1, Entity *ent2)
 *     -void handlingBouncingComponents(World *world)
 *     -bool validXCollision(Entity *ent1, Entity *ent2)
 *     -bool validYCollision(Entity *ent1, Entity *ent2)
 *     -bool checkCollisionWithObject(Entity *ent1, Entity *ent2)
 *     -void checkCollisionWithCollectible(Entity *ent1, Entity *ent2)
 *     -void checkYEnemyCollision(Entity *ent1, Entity *ent2)
 *     -void checkCollisionWithSolidObject(Entity *ent1, Entity *ent2)
 * }
 * @enduml
 */


#ifndef MARIO_MAKER_PHYSICSYSTEM_H
#define MARIO_MAKER_PHYSICSYSTEM_H
#include <raylib.h>
#include <unordered_set>
#include "ECS.h"
#include "components/Components.h"
#include "Constants.h"
#include "events/Events.h"

using namespace ECS;

class PhysicSystem : public EntitySystem {
public:

    PhysicSystem();

    void configure(World* world) override;

    void unconfigure(World* world) override;

    void tick(World* world, float delta) override;

    virtual ~PhysicSystem();

private:

    void checkIfOutsideWorld(World* world);

    void checkYCollision(Entity* ent1, Entity* ent2);

    void checkXCollision(Entity* ent1, Entity* ent2);

    void moveWalkComponents(World* world);

    void checkKineticKineticCollisions(World* world);

    void checkKineticStaticCollisions(World* world);

    void applyForces(World* world);

    void applyGravity(World* world);

    std::unordered_set<int> getNeighborIds(ComponentHandle<IdsMapComponent> map, ComponentHandle<AABBComponent> handle);

    std::vector<std::unordered_set<int>> getNeighborIds(ComponentHandle<SpacialHashMapComponent> map, ComponentHandle<AABBComponent> aabb);

    void checkIfBreakComponent(Entity *ent1, Entity *ent2);

    void checkXEnemyCollision(Entity *ent1, Entity *ent2);

    void handlingBouncingComponents(World *world);

    bool validXCollision(Entity *ent1, Entity *ent2);

    bool validYCollision(Entity *ent1, Entity *ent2);

    bool checkCollisionWithObject(Entity *ent1, Entity *ent2);

    void checkCollisionWithCollectible(Entity *ent1, Entity *ent2);

    void checkYEnemyCollision(Entity *ent1, Entity *ent2);

    void checkCollisionWithSolidObject(Entity *ent1, Entity *ent2);

    void jumpOverEnemy(Entity* player, Entity* enemy);

    void enemyOverPlayer(Entity* player, Entity* enemy);
};


#endif //MARIO_MAKER_PHYSICSYSTEM_H
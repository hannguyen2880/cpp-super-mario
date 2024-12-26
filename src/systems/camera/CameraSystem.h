/**
 * @startuml
 * class ECS::EntitySystem {
 *     +void configure(ECS::World* world)
 *     +void unconfigure(ECS::World* world)
 *     +void tick(ECS::World* world, float delta)
 * }
 * 
 * class CameraComponent {
 * }
 * 
 * class CameraSystem extends ECS::EntitySystem {
 *     +CameraSystem(int screenW, int screenH, int mapW, int mapH)
 *     +void configure(World* world) <<override>>
 *     +void unconfigure(World* world) <<override>>
 *     +void tick(World* world, float delta) <<override>>
 *     +~CameraSystem()
 *     -void followLeadPlayer(World* world)
 *     -bool checkIfDefreezeEntity(Vector2 playerPos, Vector2 entityPos)
 *     -void defreezeCloseEnemies(World *world)
 *     -CameraComponent* pCamera_
 *     -const int screenWidth_
 *     -const int screenHeight_
 *     -const int mapWidth_
 *     -const int mapHeight_
 * }
 * 
 * CameraSystem *-- CameraComponent : composes
 * @enduml
 */

#ifndef MARIO_MAKER_CAMERASYSTEM_H
#define MARIO_MAKER_CAMERASYSTEM_H

#include <raylib.h>
#include <math.h>
#include "ECS.h"

using namespace ECS;

class CameraSystem : public EntitySystem {
public:
    CameraSystem(int screenW, int screenH, int mapW, int mapH);

    void configure(World* world);

    void unconfigure(World* world);

    virtual ~CameraSystem();

    void tick(World* world, float delta);

private:

    void followLeadPlayer(World* world);

    bool checkIfDefreezeEntity(Vector2 playerPos, Vector2 entityPos);

private:
    CameraComponent* pCamera_;
    const int screenWidth_;
    const int screenHeight_;
    const int mapWidth_;
    const int mapHeight_;

    void defreezeCloseEnemies(World *world);
};

#endif //MARIO_MAKER_CAMERASYSTEM_H

/**
 * @startuml
 * class EnemyCollisionEvent {
 *     +EnemyCollisionEvent(Entity* player, Entity* enemy)
 *     +Entity* player
 *     +Entity* enemy
 * }
 * 
 * class PlayerCollectableCollisionEvent {
 *     +PlayerCollectableCollisionEvent(Entity *collectable, Entity *player)
 *     +Entity* collectable
 *     +Entity* player
 * }
 * 
 * class EnemyCollectableCollisionEvent {
 *     +EnemyCollectableCollisionEvent(Entity *collectable, Entity *enemy)
 *     +Entity* collectable
 *     +Entity* enemy
 * }
 * 
 * class BreakEvent {
 *     +float x
 *     +float y
 * }
 * 
 * class KillEnemyEvent {
 *     +explicit KillEnemyEvent(Entity* enemy)
 *     +KillEnemyEvent(Entity *enemy, bool killedByFireball)
 *     +Entity* enemy
 *     +bool killedByFireball
 * }
 * 
 * class CollisionWithFinalPoleEvent {
 *     +CollisionWithFinalPoleEvent(Entity *player, Entity* pole)
 *     +Entity* player
 *     +Entity* pole
 * }
 * 
 * class CollisionWithCoinEvent {
 *     +CollisionWithCoinEvent(Entity *player, Entity *coin)
 *     +Entity* player
 *     +Entity* coin
 * }
 * 
 * class AddScoreEvent {
 *     +AddScoreEvent(u_int16_t scoreToAdd, Vector2 position)
 *     +AddScoreEvent(u_int16_t scoreToAdd, const Vector2 &position, bool oneUpEvent)
 *     +u_int16_t scoreToAdd
 *     +Vector2 position
 *     +bool oneUpEvent
 * }
 * 
 * class SoundEvent {
 *     +SoundEvent(SoundId soundId)
 *     +SoundId soundId
 * }
 * 
 * class SetMusicEvent {
 *     +SetMusicEvent(MusicId musicId)
 *     +MusicId musicId
 * }
 * @enduml
 */
#pragma once

#include <raylib.h>
#include "ECS.h"
#include "../audio/AudioIds.h"

using namespace ECS;

struct EnemyCollisionEvent {
    EnemyCollisionEvent(Entity* player, Entity* enemy)
            : player(player), enemy(enemy) {}

    Entity* player;
    Entity* enemy;
};

struct PLayerCollectableCollisionEvent {

    PLayerCollectableCollisionEvent(Entity *collectable, Entity *player)
    : collectable(collectable), player(player) {}

    Entity* collectable;
    Entity* player;
};


struct EnemyCollectableCollisionEvent {

    EnemyCollectableCollisionEvent(Entity *collectable, Entity *enemy)
    : collectable(collectable), enemy(enemy) {}

    Entity* collectable;
    Entity* enemy;
};

struct BreakEvent {
    float x;
    float y;
};

struct KillEnemyEvent {

    explicit KillEnemyEvent(Entity* enemy): enemy(enemy) {}

    KillEnemyEvent(Entity *enemy, bool killedByFireball)
    : enemy(enemy), killedByFireball(killedByFireball) {}

    Entity* enemy;
    bool killedByFireball = false;
};

struct CollisionWithFinalPoleEvent {

    CollisionWithFinalPoleEvent(Entity *player, Entity* pole)
    : player(player), pole(pole) {}

    Entity* player;
    Entity* pole;
};

struct CollisionWithCoinEvent {

    CollisionWithCoinEvent(Entity *player, Entity *coin) : player(player), coin(coin) {}

    Entity* player;
    Entity* coin;
};

struct AddScoreEvent {

    AddScoreEvent(u_int16_t scoreToAdd, Vector2 position) : scoreToAdd(scoreToAdd), position(position) {}

    AddScoreEvent(u_int16_t scoreToAdd, const Vector2 &position, bool oneUpEvent) : scoreToAdd(scoreToAdd),
                                                                                    position(position),
                                                                                    oneUpEvent(oneUpEvent) {}

    u_int16_t scoreToAdd;
    Vector2 position;
    bool oneUpEvent = false;
};

struct SoundEvent {

    SoundEvent(SoundId soundId) : soundId(soundId) {}

    SoundId soundId;
};

struct SetMusicEvent {

    SetMusicEvent(MusicId musicId) : musicId(musicId) {}

    MusicId musicId;
};
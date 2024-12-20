#ifndef MARIO_MAKER_SCORESYSTEM_H
#define MARIO_MAKER_SCORESYSTEM_H
#include "ECS.h"
#include "events/Events.h"

using namespace ECS;

class ScoreSystem :
        public EntitySystem,
        public EventSubscriber<CollisionWithCoinEvent>,
        public EventSubscriber<AddScoreEvent> {
public:

    ScoreSystem();

    ~ScoreSystem();

    void configure(World *world) override;

    void unconfigure(World *world) override;

    void tick(World *world, ECS::DefaultTickData data) override;

    void receive(World *world, const CollisionWithCoinEvent &event) override;

    void receive(World *world, const AddScoreEvent &event) override;

private:
    ECS::Entity* textCoinCounter_;
    ECS::Entity* textScoreCounter_;

    // iterates over all entities that have a GameTextComponent
    void destroyScoreTextComponents(World *world);
};


#endif //MARIO_MAKER_SCORESYSTEM_H

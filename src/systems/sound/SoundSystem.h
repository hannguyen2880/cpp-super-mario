#pragma once
#include "ECS.h"
#include "audio/AudioManager.h"
#include "audio/AudioIds.h"
#include "events/Events.h"

using namespace ECS;

class SoundSystem :
        public EntitySystem,
        public EventSubscriber<SoundEvent>,
        public EventSubscriber<SetMusicEvent> {
public:
    SoundSystem();

    ~SoundSystem();

    void configure(World *world) override;

    void unconfigure(World *world) override;

    void tick(World *world, ECS::DefaultTickData data) override;

    void receive(World *world, const SoundEvent &event) override;

    void receive(World *world, const SetMusicEvent &event) override;

    Music getCurrentMusic();

private:
    AudioManager* audioManager_;
};


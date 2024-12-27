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
 * class SoundEvent {
 * }
 *
 * class SetMusicEvent {
 * }
 *
 * class SoundSystem extends EntitySystem {
 *     + SoundSystem()
 *     + ~SoundSystem()
 *     + void configure(World *world) <<override>>
 *     + void unconfigure(World *world) <<override>>
 *     + void tick(World *world, ECS::DefaultTickData data) <<override>>
 *     + void receive(World *world, const SoundEvent &event) <<override>>
 *     + void receive(World *world, const SetMusicEvent &event) <<override>>
 * }
 *
 * SoundSystem "1" *-- "1" ECS::Entity
 * SoundSystem <|.. EventSubscriber : implements
 * EventSubscriber <|.. SoundEvent
 * EventSubscriber <|.. SetMusicEvent
 * @enduml
 */
#ifndef MARIO_MAKER_SOUNDSYSTEM_H
#define MARIO_MAKER_SOUNDSYSTEM_H
#include "ECS.h"
#include "audio/AudioIds.h"
#include "audio/AudioManager.h"
#include "events/Events.h"

using namespace ECS;

class SoundSystem : public EntitySystem,
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
  AudioManager *audioManager_;
};

#endif // MARIO_MAKER_SOUNDSYSTEM_H

#include <supergoon_engine_export.h>
#include <supergoon_engine/objects/actor.hpp>
#include <supergoon_engine/components/animation_component.hpp>
#include <supergoon_engine/components/rigidbody_component.hpp>
#include <cstring>

std::vector<Objects::Actor::actor_factory> Objects::Actor::actor_listing_vector;
Objects::Actor::Actor(ActorParams params) : GameObject(params.loc)
{
    animation_component = new Components::AnimationComponent(this, params.actor_name.c_str(), params.layer);
    //TODO get the right size.
    rigidbody_component = new Components::RigidbodyComponent(this,Point(32));
}

Objects::Actor::~Actor()
{
}

Objects::Actor *Objects::SpawnActor(ActorParams params)
{
    // auto parser = Json::JsonParser();
    for (auto &&factory : Objects::Actor::actor_listing_vector)
    {
        auto name = factory.first;
        auto secondName = params.actor_name.c_str();
        auto is = strcmp(name, secondName);
        if (is == 0)
        {
            auto guy = factory.second(params);
            return guy;
        }
    }
    return nullptr;
}
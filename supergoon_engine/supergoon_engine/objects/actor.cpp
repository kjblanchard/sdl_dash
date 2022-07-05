#include <supergoon_engine/objects/actor.hpp>
#include <supergoon_engine/components/animation_component.hpp>
#include <supergoon_engine/json/json_parser.hpp>

std::vector<Objects::Actor::actor_factory> Objects::Actor::actor_listing_vector;
Objects::Actor::Actor(ActorParams params) : GameObject(params.loc)
{
    animation_component = new Components::AnimationComponent(this, params.actor_name);
    AddComponent(animation_component);
}

Objects::Actor::~Actor()
{
}

Objects::Actor *Objects::SpawnActor(ActorParams params)
{
    auto parser = Json::JsonParser();
    for (auto &&factory : Objects::Actor::actor_listing_vector)
    {
        auto name = factory.first;
        auto secondName = params.actor_name;
        auto is = strcmp(name, secondName);
        if (is == 0)
        {
            auto guy = factory.second(params);
            return guy;
        }
    }
    return nullptr;
}
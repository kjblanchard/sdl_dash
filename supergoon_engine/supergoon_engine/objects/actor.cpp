#include <supergoon_engine/objects/actor.hpp>

using namespace Objects;

Actor::Actor(ActorParams params) : GameObject(params.loc)
{
}

Actor::~Actor()
{
}

Actor *Objects::SpawnActor(ActorParams params)
{
    for (auto &&factory : actor_listing_vector)
    {
        if (params.actor_name == factory.first)
        {
            return factory.second(params);
        }
    }
    return nullptr;
}
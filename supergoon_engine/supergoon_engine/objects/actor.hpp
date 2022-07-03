#pragma once
#include <supergoon_engine/engine/gameobject.hpp>
#include <supergoon_engine_export.h>
#include <vector>
#include <functional>

namespace Objects
{
    struct ActorParams
    {
        Vector2 loc;
        const char* actor_name;
    };

    class Actor : public GameObject
    {
    private:
    protected:
         Actor(ActorParams params);
        ~Actor() override;

    public:
    virtual Actor* ActorFactory(ActorParams& params) = 0;
    };

typedef std::pair<const char*, std::function<Actor*(ActorParams&)>> actor_factory;

static std::vector<actor_factory> actor_listing_vector;
Actor* SpawnActor(ActorParams params);


}

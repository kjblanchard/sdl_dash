#pragma once
// #define SDL_MAIN_HANDLED
#include <supergoon_engine/engine/gameobject.hpp>
#include <supergoon_engine_export.h>
#include <vector>
#include <functional>

namespace Components
{

    class AnimationComponent;
}
namespace Objects
{
    struct ActorParams
    {
        Vector2 loc;
        // const char *actor_name;
        std::string actor_name;
    };

    class Actor : public GameObject
    {
    private:
    protected:
        Actor(ActorParams params);
        ~Actor() override;
        typedef std::pair<const char *, std::function<Actor *(ActorParams &)>> actor_factory;
        Components::AnimationComponent *animation_component;

    public:
        static std::vector<actor_factory> actor_listing_vector;
    };

    Actor *SpawnActor(ActorParams params);

}

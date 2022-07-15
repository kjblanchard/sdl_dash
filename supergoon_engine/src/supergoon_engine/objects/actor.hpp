#pragma once
#include <supergoon_engine_export.h>
#include <supergoon_engine/engine/gameobject.hpp>
#include <vector>
#include <functional>

namespace Components
{
    class AnimationComponent;
}
namespace Objects
{

    struct SUPERGOON_ENGINE_EXPORT ActorParams
    {
        Vector2 loc;
        int layer;
        std::string actor_name;
    };

    class  SUPERGOON_ENGINE_EXPORT Actor : public GameObject
    {
    private:
    protected:
        Actor(ActorParams params);
        typedef std::pair<const char *, std::function<Actor *(ActorParams &)>> actor_factory;
        Components::AnimationComponent *animation_component;

    public:
        ~Actor() override;
        static std::vector<actor_factory> actor_listing_vector;
    };

    Actor *SpawnActor(ActorParams params);

}

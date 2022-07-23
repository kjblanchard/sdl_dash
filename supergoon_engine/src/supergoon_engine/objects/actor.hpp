#pragma once
#include <supergoon_engine_export.h>
#include <supergoon_engine/engine/gameobject.hpp>
#include <vector>
#include <functional>

namespace Components
{
    class AnimationComponent;
    class RigidbodyComponent;
    class InputComponent;
}
namespace Objects
{

    struct SUPERGOON_ENGINE_EXPORT ActorParams
    {
        Vector2 loc;
        int layer;
        std::string actor_name;
    };

    class SUPERGOON_ENGINE_EXPORT Actor : public GameObject
    {
    private:
    protected:
        Actor(ActorParams params);
        typedef std::pair<const char *, std::function<Actor *(ActorParams &)>> actor_factory;
        Components::AnimationComponent *animation_component;
        Components::RigidbodyComponent *rigidbody_component;
        Components::InputComponent *input_component;

        bool is_jumping = false;
        int initial_jump_multiplier = 0;
        float current_jump_length;
        float max_jump_length = 0;
        float jump_speed = 0;
        float max_run_speed = 200;
        double speed = 0;

        void UpdateMaxVelocity(Vector2 new_max);

        void ApplyMovement(const Gametime &gametime);

        void Jump(const Gametime &gametime);
        void JumpEnd();

        bool OnGround();
        bool IsFalling();
    public:
        ~Actor() override;
        static std::vector<actor_factory> actor_listing_vector;
    };

    Actor *SpawnActor(ActorParams params);

}

#pragma once
#include <supergoon_engine_export.h>
#include <supergoon_engine/engine/gameobject.hpp>
#include <supergoon_engine/primitives/rectangle.hpp>
#include <supergoon_engine/components/rigidbody_component.hpp>
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
        Rectangle box_rect;
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

        inline bool GetIsMoving()
        {
            return rigidbody_component->is_moving_x;
        }
        // inline bool GetJustStartedMoving()
        // {
        //     return rigidbody_component->just_started_moving;
        // }
        // inline void SetIsMoving(bool moving)
        // {
        //     rigidbody_component->is_moving = moving;
        // }
        // inline void SetJustStartedMoving(bool started_moving)
        // {
        //     rigidbody_component->just_started_moving = started_moving;
        // }
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

        void PrintValues();

    public:
        ~Actor() override;
        static std::vector<actor_factory> actor_listing_vector;
    };

    Actor *SpawnActor(ActorParams params);

}

#pragma once
#include <supergoon_engine_export.h>
#include <supergoon_engine/engine/gameobject.hpp>
#include <supergoon_engine/primitives/rectangle.hpp>
#include <supergoon_engine/components/rigidbody_component.hpp>
#include <supergoon_engine/components/animation_component.hpp>
#include <supergoon_engine/components/input_component.hpp>
#include <vector>
#include <functional>

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
        const char *idle_animation_name = "idle";
        const char *run_animation_name = "run";
        const char *jump_animation_name = "jump";
        const char *fall_animation_name = "fall";

        Actor(ActorParams params);
        typedef std::pair<const char *, std::function<Actor *(ActorParams &)>> actor_factory;
        Components::AnimationComponent *animation_component;
        Components::RigidbodyComponent *rigidbody_component;
        Components::InputComponent *input_component;

        inline bool GetIsMoving()
        {
            return rigidbody_component->is_moving_x;
        }
        bool is_jumping = false;
        bool is_moving_x = false;
        int initial_jump_multiplier = 0;
        float current_jump_length;
        float max_jump_length = 0;
        float jump_speed = 0;
        float max_run_speed = 200;
        double speed = 0;

        inline void UpdateMaxVelocity(Vector2 new_max)
        {
            rigidbody_component->max_velocity = new_max;
        }
        inline void UpdateMaxXVelocity(float new_max)
        {
            rigidbody_component->max_velocity.x = new_max;
        }

        inline void UpdateMaxYVelocity(float new_max)
        {
            rigidbody_component->max_velocity.y = new_max;
        }

        void ApplyMovement(const Gametime &gametime);

        void Jump(const Gametime &gametime);
        void JumpEnd();

        bool OnGround();
        bool IsFalling();

        void PrintValues();

    public:
        ~Actor() override;
        static std::vector<actor_factory> actor_listing_vector;
        void Update(const Gametime &gametime) override;
        inline virtual void ProcessInput(const Gametime &)
        {
        }
    };

    Actor *SpawnActor(ActorParams params);

}

#pragma once
#include <supergoon_engine_export.h>
#include <supergoon_engine/engine/gameobject.hpp>
#include <supergoon_engine/primitives/rectangle.hpp>
#include <supergoon_engine/interfaces/i_sound.hpp>
#include <supergoon_engine/components/rigidbody_component.hpp>
#include <supergoon_engine/components/animation_component.hpp>
#include <supergoon_engine/components/input_component.hpp>
#include <supergoon_engine/components/box_collider_component.hpp>
#include <supergoon_engine/engine/engine_tags.hpp>
#include <vector>
#include <map>
#include <functional>

namespace Objects
{

    struct SUPERGOON_ENGINE_EXPORT ActorParams
    {
        Vector2 loc;
        Vector2 size;
        int layer;
        Rectangle box_rect;
        std::string actor_name;
        std::string type;
        std::map<std::string, int> actor_props;
    };

    class SUPERGOON_ENGINE_EXPORT Actor : public GameObject, public ISound
    {
    private:
        int jump_sound = -1;

    protected:
        const char *idle_animation_name = "idle";
        const char *run_animation_name = "run";
        const char *jump_animation_name = "jump";
        const char *fall_animation_name = "fall";
        const char *action_animation_name = "action";

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

        inline void SetJumpSound(int sound_to_play){
            jump_sound = sound_to_play;
        }

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
        inline Components::RigidbodyComponent &GetRigidbody()
        {
            return *rigidbody_component;
        }
        inline virtual void ProcessInput(const Gametime &)
        {
        }
        inline std::vector<Components::BoxColliderComponent *> GetBoxColliders()
        {
            std::vector<Components::BoxColliderComponent *> box_colliders;
            std::for_each(components_.begin(), components_.end(), [&](std::shared_ptr<Component> comp)
                          {
                              if (comp->HasTag(Tags::ComponentTags::Box))
                              {
                                  box_colliders.push_back(dynamic_cast<Components::BoxColliderComponent *>(comp.get()));
                              }
                          });
            return box_colliders;
        }
    };

    Actor *SpawnActor(ActorParams params);

}

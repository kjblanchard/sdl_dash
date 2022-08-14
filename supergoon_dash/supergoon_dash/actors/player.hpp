#pragma once
#include <supergoon_engine/objects/actor.hpp>

namespace Components
{
    class CameraBoomComponent;
}

class Player : public Objects::Actor
{
private:
    void CreateAllAnimations();
    void CreateIdleAnimation();
    void CreateRunAnimation();
    void CreateFallAnimation();
    void CreateJumpAnimation();
    Components::CameraBoomComponent *camera_boom_component;

public:
    Player(Objects::ActorParams params);
    ~Player() override;
    static Objects::Actor *ActorFactory(Objects::ActorParams &params);
    void Update(const Gametime &gametime) override;
    void ProcessInput(const Gametime &) override;

    inline float SetRunAnimSpeed()
    {
        float multiplier;
        if (rigidbody_component->velocity.x >= 0)
        {
            if (rigidbody_component->velocity.x * multiplier < 30 * multiplier)
                return 0.25f;
            else if (rigidbody_component->velocity.x < 60)
                return 0.5f;
            else if (rigidbody_component->velocity.x < 150)
                return 1.0f;
            else
                return 1.25;
        }
        else
        {
            if (rigidbody_component->velocity.x > -30)
                return 0.25f;
            else if (rigidbody_component->velocity.x > -60)
                return 0.5f;
            else if (rigidbody_component->velocity.x > -150)
                return 1.0f;
            else
                return 1.25;
        }
    }

    inline void TrampolineJump(Components::OverlapDirection dir, int force)
    {
        rigidbody_component->ChangeAccelStatic(Vector2(rigidbody_component->velocity.x, force));
        animation_component->ForceAnimationChange(jump_animation_name);
    }
};

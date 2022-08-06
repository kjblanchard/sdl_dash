#include <supergoon_dash/actors/trampoline.hpp>
#include <supergoon_dash/actors/player.hpp>
#include <supergoon_engine/animation/finish_animation_transition.hpp>

Trampoline::Trampoline(Objects::ActorParams params) : Objects::Actor{params}
{
    // TODO make this a variable that is equal to the player.
    AddTag(5);
    // TODO make this automatic from the lua file.
    rigidbody_component->SetGravityEnabled(false);
    rigidbody_component->GetBoxCollider().is_blocking = true;
    rigidbody_component->GetBoxCollider().debug = true;
    rigidbody_component->AddOverlapEvent([this](Components::BoxColliderEventArgs args)
                                         {
        if (args.overlapee->HasTag(25) )
        {
            auto player = dynamic_cast<Player*>(args.overlapee);
            if (player)
            {
                    player->TrampolineJump(args.overlap_direction);
                    if(Components::OverlapDirection::Down == args.overlap_direction)
                    {
                        trampoline_bouncing = true;
                        animation_component->ForceAnimationChange(action_animation_name);

                    }

            }
        } });
    CreateAllAnimations();
}
Trampoline::~Trampoline()
{
}
Objects::Actor *Trampoline::ActorFactory(Objects::ActorParams &params)
{
    return new Trampoline(params);
}
void Trampoline::Update(const Gametime &gametime)

{
    Actor::Update(gametime);
}
void Trampoline::CreateAllAnimations()
{
    CreateIdleAnimation();
    CreateActionAnimation();
    animation_component->SetEntryAnim(idle_animation_name);
}
void Trampoline::CreateIdleAnimation()
{
    auto idle_animation = new Animations::Animation(idle_animation_name, false);
    animation_component->AddAnimation(*idle_animation);
}
void Trampoline::CreateActionAnimation()
{
    auto action_animation = new Animations::Animation(action_animation_name, false);
    auto action_to_idle_transition = new Animations::FinishAnimationTransition(idle_animation_name, action_animation);

    action_animation->AddTransition(action_to_idle_transition);
    animation_component->AddAnimation(*action_animation);
}
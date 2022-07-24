#include <supergoon_dash/actors/player.hpp>
#include <supergoon_engine/components/input_component.hpp>
#include <supergoon_engine/input/input.hpp>
#include <supergoon_engine/input/player_controller.hpp>
#include <supergoon_engine/components/camera_boom_component.hpp>
#include <supergoon_engine/animation/animation.hpp>
#include <supergoon_engine/components/animation_component.hpp>

using namespace Components;

Player::Player(Objects::ActorParams params) : Objects::Actor{params}
{
    auto first_controller = Input::GetPlayerController(0);
    input_component->TakeControl(first_controller);
    // TODO move these to a player.lua.
    speed = 220;
    jump_speed = 210;
    max_jump_length = 0.35f;
    initial_jump_multiplier = 60;
    // TODO make this a variable that is equal to the player.
    AddTag(25);
    // TODO make this automatic from the lua file.
    UpdateMaxXVelocity(200);
    new CameraBoomComponent(this, *main_camera);
    CreateAllAnimations();
}
void Player::Update(const Gametime &gametime)
{
    Actor::Update(gametime);
}

Player::~Player()
{
}

Objects::Actor *Player::ActorFactory(Objects::ActorParams &params)
{
    return new Player(params);
}

void Player::ProcessInput(const Gametime &gametime)
{
    if (input_component->CurrentController->IsButtonPressed(Input::ControllerButtons::Left) ||
        input_component->CurrentController->IsButtonHeld(Input::ControllerButtons::Left))
    {
        auto frame_speed = (rigidbody_component->velocity.x == 0.f) ? speed * 10 * gametime.ElapsedTimeInSeconds() : speed * gametime.ElapsedTimeInSeconds();
        rigidbody_component->ApplyForce(Vector2(-frame_speed, 0));
    }
    if (input_component->CurrentController->IsButtonPressed(Input::ControllerButtons::Right) ||
        input_component->CurrentController->IsButtonHeld(Input::ControllerButtons::Right))
    {
        auto frame_speed = (rigidbody_component->velocity.x == 0.f) ? speed * 10 * gametime.ElapsedTimeInSeconds() : speed * gametime.ElapsedTimeInSeconds();
        rigidbody_component->ApplyForce(Vector2(frame_speed, 0));
    }

    if (input_component->CurrentController->IsButtonPressed(Input::ControllerButtons::A) ||
        input_component->CurrentController->IsButtonHeld(Input::ControllerButtons::A))
    {
        Jump(gametime);
    }
    else if (input_component->CurrentController->IsButtonReleased(Input::ControllerButtons::A))
    {
        JumpEnd();
    }
}
void Player::CreateAllAnimations()
{
    CreateIdleAnimation();
    CreateRunAnimation();
    CreateJumpAnimation();
    CreateFallAnimation();
    animation_component->SetEntryAnim(idle_animation_name);
}
void Player::CreateIdleAnimation()
{
    auto idle_animation = new Animations::Animation(idle_animation_name);

    auto idle_to_run_transition = Animations::AnimationTransition(run_animation_name, [this]()
                                                                  { return rigidbody_component->acceleration.x != 0.f || rigidbody_component->velocity.x > rigidbody_component->GetMinimumXStep() ||
                                                                           rigidbody_component->velocity.x <= -rigidbody_component->GetMinimumXStep(); });

    auto idle_to_jump_transition = Animations::AnimationTransition(jump_animation_name, [this]()
                                                                   { return is_jumping; });

    auto idle_to_fall_transition = Animations::AnimationTransition(fall_animation_name, [this]()
                                                                   { return IsFalling() == true; });
    idle_animation->AddTransition(idle_to_fall_transition);
    idle_animation->AddTransition(idle_to_run_transition);
    idle_animation->AddTransition(idle_to_jump_transition);
    animation_component->AddAnimation(*idle_animation);
}
void Player::CreateRunAnimation()
{
    auto run_animation = new Animations::Animation(run_animation_name);
    auto run_to_idle_transition = Animations::AnimationTransition(idle_animation_name, [this]()
                                                                  { return rigidbody_component->velocity.x == 0.f && rigidbody_component->acceleration.x == 0.f; });

    auto run_to_jump_transition = Animations::AnimationTransition(jump_animation_name, [this]()
                                                                  { return is_jumping == true; });

    auto run_to_fall_transition = Animations::AnimationTransition(fall_animation_name, [this]
                                                                  { return IsFalling() == true; });
    run_animation->AddTransition(run_to_fall_transition);
    run_animation->AddTransition(run_to_idle_transition);
    run_animation->AddTransition(run_to_jump_transition);
    animation_component->AddAnimation(*run_animation);
}
void Player::CreateFallAnimation()
{
    auto fall_animation = new Animations::Animation(fall_animation_name, false);
    auto fall_to_idle_transition = Animations::AnimationTransition(idle_animation_name, [this]()
                                                                   { return is_jumping == false && OnGround() == true; });
    fall_animation->AddTransition(fall_to_idle_transition);

    auto fall_to_jump_transition = Animations::AnimationTransition(jump_animation_name, [this]()
                                                                   { return is_jumping == true && OnGround() == true; });
    fall_animation->AddTransition(fall_to_jump_transition);
    animation_component->AddAnimation(*fall_animation);
}
void Player::CreateJumpAnimation()
{
    auto jump_animation = new Animations::Animation(jump_animation_name, false);
    auto jump_to_fall_transition = Animations::AnimationTransition(fall_animation_name, [this]()
                                                                   { return is_jumping == false; });
    jump_animation->AddTransition(jump_to_fall_transition);
    animation_component->AddAnimation(*jump_animation);
}

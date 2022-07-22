#include <supergoon_dash/actors/player.hpp>
#include <supergoon_engine/components/input_component.hpp>
#include <supergoon_engine/input/input.hpp>
#include <supergoon_engine/input/player_controller.hpp>
#include <supergoon_engine/components/rigidbody_component.hpp>
#include <supergoon_engine/components/camera_boom_component.hpp>
#include <supergoon_engine/animation/animation.hpp>
#include <supergoon_engine/components/animation_component.hpp>

using namespace Components;

Player::Player(Objects::ActorParams params) : Objects::Actor{params}
{
    auto first_controller = Input::GetPlayerController(0);

    input_component->TakeControl(first_controller);
    speed = 190;
    jump_speed = 100;
    max_jump_length = 0.5;
    initial_jump_multiplier = 100;
    AddTag(25);
    // TODO make it so that we can just set one.
    UpdateMaxVelocity(Vector2(200, 1000));
    auto boom = new CameraBoomComponent(this, *main_camera);
    CreateAllAnimations();
}
void Player::Update(const Gametime &gametime)
{
    Actor::Update(gametime);
    if (input_component->CurrentController->IsButtonPressed(Input::ControllerButtons::Left) ||
        input_component->CurrentController->IsButtonHeld(Input::ControllerButtons::Left))
    {
        auto frame_speed = static_cast<double>(speed) * gametime.ElapsedTimeInSeconds();
        rigidbody_component->ApplyForce(Vector2(-static_cast<float>(frame_speed), 0));
    }
    if (input_component->CurrentController->IsButtonPressed(Input::ControllerButtons::Right) ||
        input_component->CurrentController->IsButtonHeld(Input::ControllerButtons::Right))
    {
        // Get a speed boost when you aren't moving, to overcome initial friction.
        auto frame_speed = (rigidbody_component->velocity.x == 0.f) ? speed * 10 * gametime.ElapsedTimeInSeconds() : speed * gametime.ElapsedTimeInSeconds();
        rigidbody_component->ApplyForce(Vector2(static_cast<float>(frame_speed), 0));
    }
    if (input_component->CurrentController->IsButtonPressed(Input::ControllerButtons::A) ||
        input_component->CurrentController->IsButtonHeld(Input::ControllerButtons::A))
    {
        Jump(gametime);
    }
    if (input_component->CurrentController->IsButtonReleased(Input::ControllerButtons::A))
    {
        JumpEnd();
    }
}

Player::~Player()
{
}
Objects::Actor *Player::ActorFactory(Objects::ActorParams &params)
{
    return new Player(params);
}
void Player::CreateAllAnimations()
{
    // Animation names;
    auto idle_animation_name = "idle";
    auto run_animation_name = "run";
    // Create Animations
    auto idle_animation = new Animations::Animation(idle_animation_name);
    auto run_animation = new Animations::Animation(run_animation_name);

    // Idle to run transition
    Animations::AnimationTransition idle_to_run_transition;
    idle_to_run_transition.new_transition = run_animation_name;
    idle_to_run_transition.transition_function = [this]()
    {
        return rigidbody_component->velocity.x != 0.f;
    };
    idle_animation->AddTransition(idle_to_run_transition);

    Animations::AnimationTransition run_to_idle_transition;
    run_to_idle_transition.new_transition = idle_animation_name;
    run_to_idle_transition.transition_function = [this]()
    {
        return rigidbody_component->velocity.x == 0.f;
    };
    run_animation->AddTransition(run_to_idle_transition);

    // Add animations
    animation_component->AddAnimation(*idle_animation);
    animation_component->AddAnimation(*run_animation);

    // Add the entry animation
    animation_component->SetEntryAnim(idle_animation_name);
}

bool Player::IdleToRunTransition()
{
    return rigidbody_component->velocity.x != 0.f;
}

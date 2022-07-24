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
    speed = 220;
    jump_speed = 210;
    max_jump_length = 0.35f;
    initial_jump_multiplier = 60;
    AddTag(25);
    // TODO make it so that we can just set one.
    UpdateMaxVelocity(Vector2(200, 1000));
    new CameraBoomComponent(this, *main_camera);
    CreateAllAnimations();
}
void Player::Update(const Gametime &gametime)
{
    // SetIsMoving(false);
    if (input_component->CurrentController->IsButtonPressed(Input::ControllerButtons::Left) ||
        input_component->CurrentController->IsButtonHeld(Input::ControllerButtons::Left))
    {
        auto frame_speed = (rigidbody_component->velocity.x == 0.f) ? speed * 10 * gametime.ElapsedTimeInSeconds() : speed * gametime.ElapsedTimeInSeconds();
        rigidbody_component->ApplyForce(Vector2(-frame_speed, 0));
    }
    if (input_component->CurrentController->IsButtonPressed(Input::ControllerButtons::Right) ||
        input_component->CurrentController->IsButtonHeld(Input::ControllerButtons::Right))
    {
        // Get a speed boost when you aren't moving, to overcome initial friction.
        auto frame_speed = (rigidbody_component->velocity.x == 0.f) ? speed * 10 * gametime.ElapsedTimeInSeconds() : speed * gametime.ElapsedTimeInSeconds();
        rigidbody_component->ApplyForce(Vector2(frame_speed, 0));
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

    // Handle mirroring
    if (rigidbody_component->velocity.x != 0.f)
    {
        if (rigidbody_component->velocity.x < 0)
        {
            animation_component->SetMirror(true);
        }
        else
        {
            animation_component->SetMirror(false);
        }
    }
    PrintValues();
    // This updates all components
    Actor::Update(gametime);
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
    auto jump_animation_name = "jump";
    auto fall_animation_name = "fall";
    // Create Animations
    auto idle_animation = new Animations::Animation(idle_animation_name);
    auto run_animation = new Animations::Animation(run_animation_name);
    auto jump_animation = new Animations::Animation(jump_animation_name, false);
    auto fall_animation = new Animations::Animation(fall_animation_name, false);

    // Idle to run transition
    Animations::AnimationTransition idle_to_run_transition;
    idle_to_run_transition.new_transition = run_animation_name;
    idle_to_run_transition.transition_function = [this]()
    {
        return (rigidbody_component->acceleration.x != 0.f &&  (rigidbody_component->velocity.x > rigidbody_component->GetMinimumXStep()) ||
                rigidbody_component->velocity.x < -rigidbody_component->GetMinimumXStep());
    };
    idle_animation->AddTransition(idle_to_run_transition);

    // Idle to jump transition
    Animations::AnimationTransition idle_to_jump_transition;
    idle_to_jump_transition.new_transition = jump_animation_name;
    idle_to_jump_transition.transition_function = [this]()
    {
        return is_jumping;
    };
    idle_animation->AddTransition(idle_to_jump_transition);
    // Idle to fall transition
    Animations::AnimationTransition idle_to_fall_transition;
    idle_to_fall_transition.new_transition = fall_animation_name;
    idle_to_fall_transition.transition_function = [this]()
    {
        return IsFalling() == true;
    };
    idle_animation->AddTransition(idle_to_fall_transition);

    // jump to fall transition
    Animations::AnimationTransition jump_to_fall_transition;
    jump_to_fall_transition.new_transition = fall_animation_name;
    jump_to_fall_transition.transition_function = [this]()
    {
        return is_jumping == false;
    };
    jump_animation->AddTransition(jump_to_fall_transition);

    // fall to idle transition
    Animations::AnimationTransition fall_to_idle_transition;
    fall_to_idle_transition.new_transition = idle_animation_name;
    fall_to_idle_transition.transition_function = [this]()
    {
        return is_jumping == false && OnGround() == true;
    };
    fall_animation->AddTransition(fall_to_idle_transition);

    // fall to jump transition
    Animations::AnimationTransition fall_to_jump_transition;
    fall_to_jump_transition.new_transition = jump_animation_name;
    fall_to_jump_transition.transition_function = [this]()
    {
        return is_jumping == true && OnGround() == true;
    };
    fall_animation->AddTransition(fall_to_jump_transition);

    // Run to idle transition
    Animations::AnimationTransition run_to_idle_transition;
    run_to_idle_transition.new_transition = idle_animation_name;
    run_to_idle_transition.transition_function = [this]()
    {
        return rigidbody_component->velocity.x == 0.f && rigidbody_component->acceleration.x == 0.f;
    };
    run_animation->AddTransition(run_to_idle_transition);

    // Run to jump transition
    Animations::AnimationTransition run_to_jump_transition;
    run_to_jump_transition.new_transition = jump_animation_name;
    run_to_jump_transition.transition_function = [this]()
    {
        return is_jumping == true;
    };
    run_animation->AddTransition(run_to_jump_transition);

    // Run to fall transition
    Animations::AnimationTransition run_to_fall_transition;
    run_to_fall_transition.new_transition = fall_animation_name;
    run_to_fall_transition.transition_function = [this]()
    {
        return IsFalling() == true;
    };
    run_animation->AddTransition(run_to_fall_transition);

    // Add animations
    animation_component->AddAnimation(*idle_animation);
    animation_component->AddAnimation(*run_animation);
    animation_component->AddAnimation(*jump_animation);
    animation_component->AddAnimation(*fall_animation);

    // Add the entry animation
    animation_component->SetEntryAnim(idle_animation_name);
}

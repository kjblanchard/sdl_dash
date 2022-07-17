#include <supergoon_dash/actors/player.hpp>
#include <supergoon_engine/components/input_component.hpp>
#include <supergoon_engine/input/input.hpp>
#include <supergoon_engine/input/player_controller.hpp>
#include <supergoon_engine/components/rigidbody_component.hpp>

Player::Player(Objects::ActorParams params) : Objects::Actor{params}
{
    auto first_controller = Input::GetPlayerController(0);

    input_component->TakeControl(first_controller);
    speed = 190;
    jump_speed = 1000;
    max_jump_length = 1.0;
    initial_jump_multiplier = 10;
    // TODO make it so that we can just set one.
    UpdateMaxVelocity(Vector2(200, 1000));
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
        //Get a speed boost when you aren't moving, to overcome initial friction.
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
    std::cout << "Velocity is X: " << rigidbody_component->velocity.x << " Y: " << rigidbody_component->velocity.y << std::endl;
    std::cout << "On ground is : " << rigidbody_component->on_ground << std::endl;
}

Player::~Player()
{
}
Objects::Actor *Player::ActorFactory(Objects::ActorParams &params)
{
    return new Player(params);
}

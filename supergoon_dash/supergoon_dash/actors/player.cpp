#include <supergoon_dash/actors/player.hpp>
#include <supergoon_engine/components/input_component.hpp>
#include <supergoon_engine/input/input.hpp>
#include <supergoon_engine/input/player_controller.hpp>

Player::Player(Objects::ActorParams params) : Objects::Actor{params}
{
    auto first_controller = Input::GetPlayerController(0);

    input_component->TakeControl(first_controller);
}
void Player::Update(const Gametime &gametime)
{
    Actor::Update(gametime);
    if (input_component->CurrentController->IsButtonPressed(Input::ControllerButtons::A))
        std::cout << "No way" << std::endl;
}

Player::~Player()
{
}
Objects::Actor *Player::ActorFactory(Objects::ActorParams &params)
{
    return new Player(params);
}

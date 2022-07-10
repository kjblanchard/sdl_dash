#include <supergoon_dash/actors/player.hpp>

Player::Player(Objects::ActorParams params) : Objects::Actor{params}
{
}

Player::~Player()
{
}
Objects::Actor *Player::ActorFactory(Objects::ActorParams &params)
{
    return new Player(params);
}

#include <supergoon_dash/actors/player.hpp>
using namespace Objects;

Player::Player(ActorParams params) : Actor{params}
{
}

Player::~Player()
{
}
Actor *Player::ActorFactory(ActorParams &params)
{
    return new Player(params);
}

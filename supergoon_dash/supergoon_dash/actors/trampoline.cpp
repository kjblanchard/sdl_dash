#include <supergoon_dash/actors/trampoline.hpp>

Trampoline::Trampoline(Objects::ActorParams params) : Objects::Actor{params}
{
    // TODO make this a variable that is equal to the player.
    AddTag(5);
    // TODO make this automatic from the lua file.
    rigidbody_component->SetGravityEnabled(false);
    // CreateAllAnimations();
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
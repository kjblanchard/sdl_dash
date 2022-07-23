#include <supergoon_engine_export.h>
#include <supergoon_engine/objects/actor.hpp>
#include <supergoon_engine/components/animation_component.hpp>
#include <supergoon_engine/components/rigidbody_component.hpp>
#include <supergoon_engine/components/input_component.hpp>
#include <cstring>

std::vector<Objects::Actor::actor_factory> Objects::Actor::actor_listing_vector;
Objects::Actor::Actor(ActorParams params) : GameObject(params.loc)
{
    animation_component = new Components::AnimationComponent(this, params.actor_name.c_str(), params.layer);
    // TODO get the right size.
    rigidbody_component = new Components::RigidbodyComponent(this, Point(32));
    input_component = new Components::InputComponent(this, nullptr);
}

Objects::Actor::~Actor()
{
}

bool Objects::Actor::OnGround()
{
    return rigidbody_component->on_ground;
}
bool Objects::Actor::IsFalling()
{
    return !rigidbody_component->on_ground && !is_jumping;
}

Objects::Actor *Objects::SpawnActor(ActorParams params)
{
    // auto parser = Json::JsonParser();
    for (auto &&factory : Objects::Actor::actor_listing_vector)
    {
        auto name = factory.first;
        auto secondName = params.actor_name.c_str();
        auto is = strcmp(name, secondName);
        if (is == 0)
        {
            auto guy = factory.second(params);
            return guy;
        }
    }
    return nullptr;
}

void Objects::Actor::Jump(const Gametime &gametime)
{
    if (rigidbody_component->on_ground && !is_jumping)
    {
        is_jumping = true;
        current_jump_length = 0.0;
        rigidbody_component->on_ground = false;
        auto force = jump_speed * initial_jump_multiplier * gametime.ElapsedTimeInSeconds();
        rigidbody_component->ApplyForce(Vector2(0, -force));
    }
    else if (is_jumping && !rigidbody_component->on_ground)
    {
        auto force = jump_speed * gametime.ElapsedTimeInSeconds();
        rigidbody_component->ApplyForce(Vector2(0, -force));
        current_jump_length += gametime.ElapsedTimeInSeconds();
        if (current_jump_length >= max_jump_length)
        {
            JumpEnd();
        }
    }
}
void Objects::Actor::JumpEnd()
{
    if (is_jumping)
    {
        is_jumping = false;
    }
}
void Objects::Actor::UpdateMaxVelocity(Vector2 new_max)
{
    rigidbody_component->max_velocity = new_max;
}

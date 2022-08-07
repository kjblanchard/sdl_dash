#include <supergoon_engine_export.h>
#include <supergoon_engine/objects/actor.hpp>
#include <cstring>

std::vector<Objects::Actor::actor_factory> Objects::Actor::actor_listing_vector;
Objects::Actor::Actor(ActorParams params) : GameObject(params.loc)
{
    animation_component = new Components::AnimationComponent(this, params.actor_name.c_str(), params.layer);
    rigidbody_component = new Components::RigidbodyComponent(this, params.box_rect.GetSize(), params.box_rect.GetLocation());
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
void Objects::Actor::Update(const Gametime &gametime)

{

    is_moving_x = (rigidbody_component->acceleration.x != 0 || rigidbody_component->velocity.x != 0) ? true : false;
    // Handle mirroring
    if (rigidbody_component->velocity.x != 0.f)
    {
        if (rigidbody_component->velocity.x < 0)
        {
            animation_component->SetMirror(SpriteFlip::Horizontal);
        }
        else
        {
            animation_component->SetMirror(SpriteFlip::Default);
        }
    }
    PrintValues();
    GameObject::Update(gametime);
}

void Objects::Actor::PrintValues()
{
    // for (auto &&actor : GetBoxCollider().last_frame_overlaps)
    // {
    //     std::cout << actor->id << "\n" << std::endl;
    // }

    // std::string print_value = (is_jumping) ? "True" : "False";
    // std::cout << "Our jumping value is " << print_value << std::endl;
    // std::cout << "Our velocity is X: " << rigidbody_component->velocity.x << " Y: " << rigidbody_component->velocity.y <<  std::endl;
    // print_value = (OnGround()) ? "True" : "False";
    // std::cout << "Our on ground value is " << print_value << std::endl;
}

void Objects::Actor::Jump(const Gametime &gametime)
{
    if (rigidbody_component->on_ground && !is_jumping)
    {
        is_jumping = true;
        current_jump_length = 0.0;
        rigidbody_component->on_ground = false;
        // auto force = (jump_speed * initial_jump_multiplier) * gametime.ElapsedTimeInSeconds();
        auto force = (jump_speed * initial_jump_multiplier) / 100;
        rigidbody_component->ChangeVelocityStatic(Vector2(rigidbody_component->velocity.x,-force));
        animation_component->ForceAnimationChange("jump");
    }
    else if (is_jumping && !rigidbody_component->on_ground)
    {
        auto force = jump_speed * gametime.ElapsedTimeInSeconds();
        // auto force = jump_speed / 100;
        rigidbody_component->ApplyForce(Vector2(0, -force));
        current_jump_length += gametime.ElapsedTimeInSeconds();
    }
    if (current_jump_length >= max_jump_length)
    {
        JumpEnd();
    }
}
void Objects::Actor::JumpEnd()
{
    is_jumping = false;
}

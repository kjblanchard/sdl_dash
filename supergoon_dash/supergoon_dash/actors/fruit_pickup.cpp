#include <supergoon_dash/actors/fruit_pickup.hpp>
#include <supergoon_dash/actors/player.hpp>

FruitPickup::FruitPickup(Objects::ActorParams params) : Actor{params}
{
    rigidbody_component->SetGravityEnabled(false);
    rigidbody_component->GetBoxCollider().is_blocking = false;
    rigidbody_component->GetBoxCollider().debug = true;
    rigidbody_component->AddOverlapEvent([this](Components::BoxColliderEventArgs args)
                                         {
        if (args.overlapee->HasTag(25) )
        {
            auto player = dynamic_cast<Player*>(args.overlapee);
            if (player)
            {
                        PlaySfxOneShot(5);
            }

        } });
    CreateIdleAnimation();
}

FruitPickup::~FruitPickup()
{
}
Objects::Actor *FruitPickup::ActorFactory(Objects::ActorParams &params)
{
    return new FruitPickup(params);
}

void FruitPickup::Update(const Gametime &gametime)
{
    Actor::Update(gametime);
}

void FruitPickup::CreateIdleAnimation()
{
    auto idle_animation = new Animations::Animation(idle_animation_name, true, true);
    animation_component->AddAnimation(idle_animation);
    //TODO make this default?
    animation_component->SetEntryAnim(idle_animation_name);

}


#include <supergoon_dash/actors/level_end.hpp>
#include <supergoon_dash/actors/player.hpp>
LevelEnd::LevelEnd(Objects::ActorParams params) : Objects::Actor{params}
{
    rigidbody_component->SetGravityEnabled(false);
    rigidbody_component->GetBoxCollider().is_blocking = false;
    rigidbody_component->debug = true;
    rigidbody_component->AddOverlapEvent([this](Components::BoxColliderEventArgs args)
                                         {
        if (args.overlapee->HasTag(25) )
        {
            auto player = dynamic_cast<Player*>(args.overlapee);
            if (player)
            {
                        player->EndLevel();
                        PlaySfxOneShot(5);
            }
        } });
}
LevelEnd::~LevelEnd()
{
}

Objects::Actor *LevelEnd::ActorFactory(Objects::ActorParams &params)
{
    return new LevelEnd(params);
}
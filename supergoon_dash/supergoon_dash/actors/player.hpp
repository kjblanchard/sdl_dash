#pragma once
#include <supergoon_engine/objects/actor.hpp>

class Player : public Objects::Actor
{
private:
    /* data */
public:
    Player(Objects::ActorParams params);
    ~Player() override;
    static Objects::Actor* ActorFactory(Objects::ActorParams& params);
};


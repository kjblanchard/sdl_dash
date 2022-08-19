#pragma once
#include <supergoon_engine/objects/actor.hpp>

class LevelEnd : public Objects::Actor
{
    public:
    LevelEnd(Objects::ActorParams params);
    ~LevelEnd() override;
    static Objects::Actor *ActorFactory(Objects::ActorParams &params);

};
#pragma once
#include <supergoon_engine/objects/actor.hpp>


class Trampoline : public Objects::Actor
{
private:
    // void CreateAllAnimations();
    // void CreateIdleAnimation();
    // void CreateActionAnimation();


public:
    Trampoline(Objects::ActorParams params);
    ~Trampoline() override;
    static Objects::Actor *ActorFactory(Objects::ActorParams &params);
    void Update(const Gametime &gametime) override;
};
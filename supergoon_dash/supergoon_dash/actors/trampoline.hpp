#pragma once
#include <supergoon_engine/objects/actor.hpp>


class Trampoline : public Objects::Actor
{
private:
    enum class Direction{
        Up,
        Down,
        Left,
        Right
    };
    void CreateAllAnimations();
    void CreateIdleAnimation();
    void CreateActionAnimation();
    bool trampoline_bouncing = false;
    Direction direction;



public:
    Trampoline(Objects::ActorParams params);
    ~Trampoline() override;
    static Objects::Actor *ActorFactory(Objects::ActorParams &params);
    void Update(const Gametime &gametime) override;
};
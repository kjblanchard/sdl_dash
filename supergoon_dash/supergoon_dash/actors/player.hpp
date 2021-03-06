#pragma once
#include <supergoon_engine/objects/actor.hpp>

namespace Components
{
    class CameraBoomComponent;
}

class Player : public Objects::Actor
{
private:
    void CreateAllAnimations();
    void CreateIdleAnimation();
    void CreateRunAnimation();
    void CreateFallAnimation();
    void CreateJumpAnimation();
    Components::CameraBoomComponent* camera_boom_component;


public:
    Player(Objects::ActorParams params);
    ~Player() override;
    static Objects::Actor *ActorFactory(Objects::ActorParams &params);
    void Update(const Gametime &gametime) override;
    void ProcessInput(const Gametime &) override;
};

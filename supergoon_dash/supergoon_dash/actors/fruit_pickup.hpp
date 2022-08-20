#include <supergoon_engine_export.h>
#include <supergoon_engine/objects/actor.hpp>

class FruitPickup : public Objects::Actor
{
private:
    void CreateIdleAnimation();

public:
    FruitPickup(Objects::ActorParams params);
    ~FruitPickup() override;
    static Objects::Actor *ActorFactory(Objects::ActorParams &params);
    void Update(const Gametime &gametime) override;
};
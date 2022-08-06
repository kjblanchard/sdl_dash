
#pragma once
#include <supergoon_engine_export.h>
#include <supergoon_engine/physics/gravity.hpp>
#include <vector>

namespace Components
{
    class RigidbodyComponent;
    enum class OverlapDirection;
}
namespace Objects
{
    class Actor;
}
class Tile;

namespace Physics
{
    class PhysicsParams
    {

    public:
        inline PhysicsParams(const Gametime &game_time, Components::RigidbodyComponent &rb, std::vector<Tile *> tile, std::vector<Objects::Actor *> actor, Gravity::GravityParams params) : gametime{&game_time}, rigidbody{&rb}, tiles{tile}, actors{actor}, gravity_params{params} {}
        const Gametime *gametime;
        Components::RigidbodyComponent *rigidbody;
        std::vector<Tile *> tiles;
        std::vector<Objects::Actor *> actors;
        Gravity::GravityParams gravity_params;
    };

    class StepParams
    {
    public:
        inline StepParams(double full_step_, double min_step, float &loc_to_alter_, float &vel_to_alter_, Components::OverlapDirection overlap_dir_, bool x_step_) : full_step{full_step_}, minimum_step{min_step}, loc_to_alter{&loc_to_alter_}, vel_to_alter{&vel_to_alter_}, overlap_dir{overlap_dir_}, x_step{x_step_}
        {
        }
        double full_step = 0;
        double minimum_step = 0;
        float *loc_to_alter = nullptr;
        float *vel_to_alter = nullptr;
        bool x_step;
        Components::OverlapDirection overlap_dir;
        SDL_FRect* frect = nullptr;
    };

    void
    ApplyPhysics(const Gametime &gametime, Components::RigidbodyComponent &rigidbody, std::vector<Tile *> tiles, std::vector<Objects::Actor *> actors, Gravity::GravityParams params);
    void ApplyVelocityX(PhysicsParams& params);
    void ApplyVelocityY(PhysicsParams& params);

    void TryAllMovementSteps(PhysicsParams& physics_params, StepParams& step_params);

    bool TryMovementStep(PhysicsParams& physics_params, StepParams& step_params);

}
#pragma once
#include <supergoon_engine_export.h>
#include <supergoon_engine/interfaces/i_update.hpp>
#include <supergoon_engine/interfaces/i_initialize.hpp>
#include <supergoon_engine/interfaces/i_debug.hpp>
#include <supergoon_engine/interfaces/i_draw.hpp>
#include <supergoon_engine/interfaces/i_tags.hpp>

#include <supergoon_engine/primitives/vector2.hpp>
#include <iostream>

class GameObject;
class Camera;

class World;
namespace Graphics
{
    class SpriteBatch;
}

class SUPERGOON_ENGINE_EXPORT Component : public IUpdate, public IInitialize, public IDebug, public IDraw, public ITags
{
private:
    static unsigned long int current_id;

protected:
    /**
     * Pointer to world, as a convenience function.
     */
    static World *world;
    /**
     * Pointer to Main Camera, as a convenience function.
     */
    static Camera *main_camera;

    Vector2 offset_;
    GameObject *owner_;

public:
    unsigned long int id;
    int update_order = 2;
    Vector2 GetLocation();
    Component(GameObject *owner, Vector2 offset = Vector2(), int update_override = 2);
    virtual ~Component() override;

    inline void Initialize() override {}
    inline void Update(const Gametime &) override {}
    inline Component operator<(Component &rhs)
    {
        if (update_order < rhs.update_order)
            return std::move(*this);
        return std::move(rhs);
    }
    inline virtual void Draw(Graphics::SpriteBatch &) override {}
    Component(Component &) = default;
    Component(Component &&) = default;
};

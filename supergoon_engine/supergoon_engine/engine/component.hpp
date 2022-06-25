#pragma once
#include <supergoon_engine_export.h>
#include <supergoon_engine/interfaces/IUpdate.hpp>
#include <supergoon_engine/primitives/vector2.hpp>
// class SUPERGOON_ENGINE_EXPORT Component : IUpdate
class GameObject;
class SUPERGOON_ENGINE_EXPORT Component
{
protected:
    Vector2 offset_;
    GameObject *owner_;

public:
    unsigned char update_order = 255;
    inline Component(GameObject *owner, Vector2 offset = Vector2())
    {
        offset_ = offset;
        owner_ = owner;
    }

    inline virtual ~Component() {}

    // inline void Update(const Gametime &gametime) override {}
    inline void Update(const Gametime &gametime) {}
    inline Component operator<(const Component &rhs)
    {
        if (update_order < rhs.update_order)
            return *this;
        return rhs;
    }
    inline virtual void Draw(SDL_Renderer* renderer){}
};

#pragma once
#include <supergoon_engine_export.h>
#include <supergoon_engine/interfaces/IUpdate.hpp>
#include <supergoon_engine/interfaces/i_initialize.hpp>

#include <supergoon_engine/primitives/vector2.hpp>
#include <iostream>
class GameObject;
class SUPERGOON_ENGINE_EXPORT Component : public IUpdate, public IInitialize
{
protected:
    Vector2 offset_;
    GameObject *owner_;

public:
    unsigned char update_order = 255;
    Component(GameObject *owner, Vector2 offset = Vector2());
    virtual ~Component() override;

    inline void Initialize() override {}
    inline void Update(const Gametime &) override {}
    inline Component operator<(Component &rhs)
    {
        if (update_order < rhs.update_order)
            return std::move(*this);
        return std::move(rhs);
    }
    inline virtual void Draw(SDL_Renderer *) {}

    inline Component(Component &&other)
        : offset_(std::move(other.offset_)), owner_(std::move(other.owner_))
    {
    }

    inline Component &operator=(Component other)
    {
        swap(*this, other);
        return *this;
    }

    inline friend void swap(Component &lhs, Component &rhs)
    {
        using std::swap;
        swap(lhs, rhs);
    }
};

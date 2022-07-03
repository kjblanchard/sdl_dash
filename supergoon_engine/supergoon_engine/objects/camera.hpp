#pragma once
#include <supergoon_engine_export.h>
#include <supergoon_engine/engine/gameobject.hpp>

class Camera : public GameObject
{
private:
    /* data */

public:
    Camera(Vector2 loc);
    ~Camera() override;
    SDL_Rect rect;
    void Update(const Gametime &gametime) override;
};

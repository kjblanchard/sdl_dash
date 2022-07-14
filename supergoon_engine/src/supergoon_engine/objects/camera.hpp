#pragma once
#include <supergoon_engine_export.h>
#include <supergoon_engine/engine/gameobject.hpp>

namespace Graphics
{

    class GraphicsDevice;
}

class Camera : public GameObject
{
private:
    Graphics::GraphicsDevice *graphics_device;

public:
    Camera(Vector2 loc, Graphics::GraphicsDevice *graphics);
    ~Camera() override;
    SDL_Rect rect;
    void Update(const Gametime &gametime) override;
    double GetResolutionScaleSizeX();
    double GetResolutionScaleSizeY();
    void MoveCamera(Vector2 move_amount);

};

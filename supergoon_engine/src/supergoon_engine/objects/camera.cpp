#include <supergoon_engine/objects/camera.hpp>
#include <supergoon_engine/engine/world.hpp>
#include <supergoon_engine/graphics/graphics_device.hpp>
#include <supergoon_engine/primitives/point.hpp>
// TODO probably don't use this at all here.
#include <supergoon_engine/engine/level.hpp>

Camera::Camera(Vector2 loc, Graphics::GraphicsDevice *graphics) : GameObject(loc)
{
    graphics_device = graphics;
    rect.w = graphics_device->unscaled_width;
    rect.h = graphics_device->unscaled_height;
}

Camera::~Camera()
{
}

void Camera::Update(const Gametime &)
{
    location += next_frame_move;
    next_frame_move = Vector2::Zero();
    // Keep camera in level bounds.
    if (location.x < 0)
    {
        location.x = 0;
    }
    if (Level::current_level_size.x != 0.f)
    {
        if (location.x + (rect.w) >= Level::current_level_size.x)
        {
            location.x = Level::current_level_size.x - rect.w;
        }
    }
    rect.x = location.x;
    rect.y = location.y;
}

double Camera::GetResolutionScaleSizeX()
{
    return graphics_device->screen_scale_ratio_width;
}
double Camera::GetResolutionScaleSizeY()
{
    return graphics_device->screen_scale_ratio_height;
}

void Camera::MoveCamera(Vector2 move_amount)
{
    next_frame_move += move_amount;
}

Vector2 Camera::GetWorldSize()
{

    return Vector2(graphics_device->unscaled_width, graphics_device->unscaled_height);
}
#include <supergoon_engine/objects/camera.hpp>
#include <supergoon_engine/engine/world.hpp>
#include <supergoon_engine/graphics/graphics_device.hpp>
#include <supergoon_engine/primitives/point.hpp>
Camera::Camera(Vector2 loc, Graphics::GraphicsDevice *graphics) : GameObject(loc)
{
    graphics_device = graphics;
    rect.w = graphics_device->unscaled_width;
    rect.h = graphics_device->unscaled_height;
}

Camera::~Camera()
{
}

void Camera::Update(const Gametime &gametime)
{
    rect.x = location.ToPoint().x;
    rect.y = location.ToPoint().y;
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
    move_amount.x *= graphics_device->screen_scale_ratio_width;
    move_amount.y *= graphics_device->screen_scale_ratio_height;
    location.x += move_amount.x;
    location.y += move_amount.y;

}
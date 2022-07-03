#include <supergoon_engine/objects/camera.hpp>
#include <supergoon_engine/engine/world.hpp>
#include <supergoon_engine/graphics/graphics_device.hpp>
#include <supergoon_engine/primitives/point.hpp>
Camera::Camera(Vector2 loc, Graphics::GraphicsDevice *graphics) : GameObject(loc)
{
    graphics_device = graphics;
}

Camera::~Camera()
{
}

void Camera::Update(const Gametime &gametime)
{
    rect.x = location.ToPoint().x;
    rect.y = location.ToPoint().y;
    rect.w = graphics_device->unscaled_width;
    rect.h = graphics_device->unscaled_height;
    printf("Camera rect X: %d, Y: %d", rect.x, rect.y);
}

//TODO this could cause some issues, maybe get the doubles straight to help reduct some jitter.
Vector2 Camera::GetResolutionScaleSize()
{
    return Vector2(
        graphics_device->screenScaleRatioWidth,
        graphics_device->screenScaleRatioHeight
    );
}

void Camera::MoveCamera(Vector2 move_amount)
{
    move_amount.x *= graphics_device->screenScaleRatioWidth;
    move_amount.y *= graphics_device->screenScaleRatioHeight;
    location.x += move_amount.x;
    location.y += move_amount.y;


}
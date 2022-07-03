#include <supergoon_engine/objects/camera.hpp>
#include <supergoon_engine/engine/world.hpp>
#include <supergoon_engine/primitives/point.hpp>
Camera::Camera(Vector2 loc) : GameObject(loc)
{
}

Camera::~Camera()
{
}

void Camera::Update(const Gametime &gametime)
{
    rect.x = location.ToPoint().x;
    rect.y = location.ToPoint().y;
    rect.w = world->unscaled_width;
    rect.h = world->unscaled_height;
    printf("Camera rect X: %d, Y: %d", rect.x, rect.y);
}
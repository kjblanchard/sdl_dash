#include <supergoon_engine/components/camera_boom_component.hpp>
#include <supergoon_engine/objects/camera.hpp>

namespace Components
{
    CameraBoomComponent::CameraBoomComponent(GameObject *owner, Camera &camera_to_control) : Component{owner}, camera{&camera_to_control}, screen_half_width{static_cast<int>(camera->GetWorldSize().x) / 2}
    {
    }
    CameraBoomComponent::~CameraBoomComponent()
    {
    }

    void CameraBoomComponent::Update(const Gametime &)
    {
        if (owner_->location.x < screen_half_width)
            return;
        auto diff = (owner_->location.x - camera->location.x) - screen_half_width;
        camera->MoveCamera(Vector2(diff, 0));
    }
}

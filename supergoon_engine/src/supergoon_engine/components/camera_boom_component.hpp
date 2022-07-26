#pragma once
#include <supergoon_engine_export.h>
#include <supergoon_engine/engine/component.hpp>

class GameObject;
class Camera;
namespace Components
{
    class SUPERGOON_ENGINE_EXPORT  CameraBoomComponent : public Component
    {
    private:
        Camera *camera;
        int screen_half_width;

    public:
        CameraBoomComponent(GameObject *owner, Camera &camera_to_control);
        void Update(const Gametime &gametime) override;
        ~CameraBoomComponent() override;
    };
}
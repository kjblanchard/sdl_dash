#pragma once
#include <functional>
#include <supergoon_engine_export.h>
#include <supergoon_engine/engine/component.hpp>
#include <supergoon_engine/primitives/point.hpp>
#include <supergoon_engine/primitives/vector2.hpp>
#include <supergoon_engine/primitives/rectangle.hpp>
#include <supergoon_engine/engine/gameobject.hpp>
#include <supergoon_engine/objects/camera.hpp>

namespace Components
{
    class BoxColliderComponent : public Component
    {

    public:
        BoxColliderComponent(GameObject *owner, Point box_size, Vector2 offset = Vector2());
        ~BoxColliderComponent() override;
        std::vector<GameObject*> last_frame_overlaps;
        std::vector<GameObject*> this_frame_overlaps;
        Rectangle rectangle;
        Rectangle temp_rect;
        SDL_Rect GetCurrentSdlRect();
        void Update(const Gametime &gametime) override;
        void Draw(Graphics::SpriteBatch &spritebatch) override;

        std::vector<std::function<void(GameObject*)>> overlap_events;

        inline void OnOverlapBeginEvent(GameObject* overlapee)
        {
            for (auto &&i : overlap_events)
            {
                i(overlapee);
            }
        }
    };

    // struct BoxColliderEventArgs
    // {
    //     GameObject *owner;
    //     std::function<void(BoxColliderComponent &)> box_function;
    //     inline BoxColliderEventArgs(GameObject *owner_, std::function<void(BoxColliderComponent &)> other_box) : owner{owner_}, box_function{other_box}
    //     {
    //     }
    // };
}
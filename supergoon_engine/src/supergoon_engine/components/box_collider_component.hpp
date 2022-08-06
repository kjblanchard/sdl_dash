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
    enum struct OverlapDirection
    {
        Default,
        Up,
        Right,
        Down,
        Left
    };

    struct BoxColliderEventArgs
    {
        GameObject *overlapee;
        OverlapDirection overlap_direction;
        inline BoxColliderEventArgs(GameObject *owner_, OverlapDirection direction_of_overlap) : overlapee{owner_}, overlap_direction{direction_of_overlap}
        {
        }
    };
    class BoxColliderComponent : public Component
    {

    public:
        BoxColliderComponent(GameObject *owner, Point box_size, Vector2 offset = Vector2());
        ~BoxColliderComponent() override;
        std::vector<unsigned long int> last_frame_overlaps;
        std::vector<unsigned long int> this_frame_overlaps;
        Rectangle rectangle;
        Rectangle temp_rect;
        bool is_blocking = true;
        SDL_Rect GetCurrentSdlRect();
        SDL_FRect GetCurrentSdlRectF();
        void Update(const Gametime &gametime) override;
        void Draw(Graphics::SpriteBatch &spritebatch) override;

        inline void AddToOverlaps(unsigned long int overlap, BoxColliderEventArgs &args)
        {
            this_frame_overlaps.push_back(overlap);
            if (CheckIfOverlapJustBegan(overlap))
            {
                OnOverlapBeginEvent(args);
            }
        }

        inline void AddToOverlaps(GameObject *overlap, BoxColliderEventArgs &args)
        {
            AddToOverlaps(overlap->id, args);
        }
        inline void AddToOverlaps(Component *overlap, BoxColliderEventArgs &args)
        {
            AddToOverlaps(overlap->id, args);
            // this_frame_overlaps.push_back(overlap->id);
        }

        inline bool CheckIfOverlapJustBegan(unsigned long int id_)
        {
            return std::find(last_frame_overlaps.begin(), last_frame_overlaps.end(), id_) == last_frame_overlaps.end();
        }

        std::vector<std::function<void(BoxColliderEventArgs)>> overlap_events;

        inline void OnOverlapBeginEvent(BoxColliderEventArgs args)
        {
            for (auto &&i : overlap_events)
            {
                i(args);
            }
        }
    };

}
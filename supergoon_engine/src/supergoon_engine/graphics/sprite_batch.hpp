#include <vector>
#include <supergoon_engine/primitives/rectangle.hpp>

struct Sprite;

namespace Graphics
{

    class GraphicsDevice;
    class SpriteBatch
    {
        struct DrawObject
        {
            Sprite *sprite;
            Rectangle *dst_rect;
            Rectangle *src_rect;
            int layer;
        };

    private:
        GraphicsDevice *graphics_device;
        std::vector<DrawObject> draw_objects;
        std::vector<Rectangle*> draw_rects;

    public:
        SpriteBatch(GraphicsDevice *graphics);
        ~SpriteBatch();
        void Begin();
        void Draw(Sprite &sprite, Rectangle &dst_rect, Rectangle &src_rect, int layer = 0);
        void DrawUi(Sprite &sprite, Rectangle &dst_rect, Rectangle &src_rect, int layer = 0);
        void DrawRect(Rectangle& dst_rect);
        void DrawRectUi(Rectangle& dst_rect);
        void End();
    };

}
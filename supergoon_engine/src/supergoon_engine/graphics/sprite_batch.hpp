#include <vector>
#include <supergoon_engine/primitives/rectangle.hpp>

class GameObject;
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
        };

    private:
        GraphicsDevice *graphics_device;
        std::vector<DrawObject> draw_objects;

    public:
        SpriteBatch(GraphicsDevice *graphics);
        ~SpriteBatch();
        void Begin();
        void Draw(Sprite &sprite, Rectangle &dst_rect, Rectangle &src_rect);
        void End();
    };

}
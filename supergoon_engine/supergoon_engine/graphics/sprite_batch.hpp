
class GameObject;
namespace Graphics
{

    class GraphicsDevice;
    class SpriteBatch
    {
    private:
        GraphicsDevice *graphics_device;

    public:
        SpriteBatch(GraphicsDevice *graphics);
        ~SpriteBatch();
        void Begin();
        void Draw(GameObject* game_object);
        void End();
    };

}
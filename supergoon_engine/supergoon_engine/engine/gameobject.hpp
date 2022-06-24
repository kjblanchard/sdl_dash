#pragma once
#include <supergoon_engine_export.h>
#include <supergoon_engine/interfaces/IUpdate.hpp>
#include <supergoon_engine/primitives/vector2.hpp>


class World;
class SUPERGOON_ENGINE_EXPORT GameObject : public IUpdate
{
private:
    /* data */
    SDL_Texture* texture;
protected:


public:
//TODO make this not public
    static World* world;
    GameObject(Vector2 loc = Vector2());
    virtual ~GameObject();

    void Update(const Gametime& gametime) override;
    void Draw(SDL_Renderer* renderer);
    Vector2 location;
};

#pragma once
#include <supergoon_engine_export.h>
#include <supergoon_engine/interfaces/IUpdate.hpp>
#include <supergoon_engine/primitives/vector2.hpp>
#include <supergoon_engine/engine/component.hpp>
#include <vector>
#include <memory>
#include <algorithm>

class World;
class SUPERGOON_ENGINE_EXPORT GameObject : public IUpdate
{
private:
    /* data */
protected:
//TODO for some reason unique ptrs don't compile on windows (msvc), spent a bit of time on this but couldn't get it to work so just used shared
    std::vector<std::shared_ptr<Component>> components_;


public:
//TODO make this not public
    static World* world;
    GameObject(Vector2 loc = Vector2());
    virtual ~GameObject() override;

    void Update(const Gametime& gametime) override;
    void Draw(SDL_Renderer* renderer);
    Vector2 location;
     inline void AddComponent(Component* component)
     {
         components_.push_back(std::unique_ptr<Component>(component));
         std::sort(components_.begin(), components_.end());
     }
};

#pragma once
#include <supergoon_engine_export.h>
#include <supergoon_engine/engine/component.hpp>


class SUPERGOON_ENGINE_EXPORT SpriteComponent : public Component
{
private:
    /* data */
public:
    SDL_Texture* texture;
    SpriteComponent(GameObject* owner);
    void Draw(SDL_Renderer* renderer) override;
    ~SpriteComponent();
};


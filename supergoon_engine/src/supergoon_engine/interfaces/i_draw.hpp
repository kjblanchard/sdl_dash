#pragma once
#include <supergoon_engine_export.h>

namespace Graphics{
    class SpriteBatch;
}

class IDraw
{
public:
    virtual ~IDraw();
    virtual void Draw(Graphics::SpriteBatch& spritebatch) = 0;
    bool visible = true;
};

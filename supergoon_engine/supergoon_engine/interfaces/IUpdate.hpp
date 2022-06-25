#pragma once
#include <supergoon_engine_export.h>
#include <supergoon_engine/primitives/gametime.hpp>

class SUPERGOON_ENGINE_EXPORT IUpdate
{
public:
    virtual void Update(const Gametime &gametime) = 0;
    virtual ~IUpdate();
    bool Enabled = true;
};

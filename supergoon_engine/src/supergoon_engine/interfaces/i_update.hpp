#pragma once
#include <supergoon_engine_export.h>
#include <supergoon_engine/primitives/gametime.hpp>

class SUPERGOON_ENGINE_EXPORT IUpdate
{
public:
    inline IUpdate() {}
    virtual void Update(const Gametime &gametime) = 0;
    virtual ~IUpdate();
    bool Enabled = true;

    // IUpdate(const IUpdate &) = default;
    // IUpdate(IUpdate &&) = default;
    // IUpdate &operator=(const IUpdate &) = default;
    // IUpdate &operator=(IUpdate &&) = default;
};

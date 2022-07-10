#pragma once
#include <supergoon_engine_export.h>

class SUPERGOON_ENGINE_EXPORT IInitialize
{
public:
    inline IInitialize() {}
    virtual void Initialize() = 0;
    virtual ~IInitialize();
    bool initialized = true;

    // IInitialize(const IInitialize &) = default;
    // IInitialize(IInitialize &&) = default;
    // IInitialize &operator=(const IInitialize &) = default;
    // IInitialize &operator=(IInitialize &&) = default;
};
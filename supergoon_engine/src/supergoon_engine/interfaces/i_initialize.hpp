#pragma once
#include <supergoon_engine_export.h>

class SUPERGOON_ENGINE_EXPORT IInitialize
{
public:
    virtual void Initialize() = 0;
    virtual ~IInitialize();
    bool initialized = true;
};
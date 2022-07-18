#pragma once
#include <supergoon_engine_export.h>

class SUPERGOON_ENGINE_EXPORT IDebug
{
public:
    IDebug() = default;
    virtual ~IDebug();
    bool debug = false;
    IDebug(IDebug &) = default;
    IDebug(IDebug &&) = default;
};

#pragma once
#include <supergoon_engine_export.h>

class IDebug
{
public:
    IDebug() = default;
    virtual ~IDebug();
    bool debug = false;
    IDebug(IDebug &) = default;
    IDebug(IDebug &&) = default;
};

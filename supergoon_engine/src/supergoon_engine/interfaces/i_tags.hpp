#pragma once
#include <supergoon_engine_export.h>
#include <algorithm>
#include <vector>
#include <cstdarg>

class SUPERGOON_ENGINE_EXPORT ITags
{
public:
    std::vector<int> tags;

    inline void AddTag(int tag)
    {
        tags.push_back(tag);
    }

    inline bool HasTag(int search_tag)
    {
        auto thing = std::find(tags.begin(), tags.end(), search_tag);
        if(thing != tags.end())
            return true;
        return false;
    }
};
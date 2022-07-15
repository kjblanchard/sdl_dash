#pragma once
#include <supergoon_engine_export.h>
#include <vector>
#include <cstdarg>

class ITags
{
public:
    std::vector<int> tags;

    inline void AddTag(int tag, ...)
    {
        va_list var_args;
        va_start(var_args, tag);
        for (int i = 0; i < tag; i++)
        {
            tags.push_back(va_arg(var_args, int));
        }

        va_end(var_args);
    }

    inline bool HasTag(int search_tag)
    {
        for (auto i : tags)
        {
            if (i == search_tag)
                return true;
            return false;
        }
    }
};
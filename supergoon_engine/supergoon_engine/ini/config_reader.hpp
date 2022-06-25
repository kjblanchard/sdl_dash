#pragma once
#include <supergoon_engine/ini/ini.hpp>
#include <supergoon_engine_export.h>

class SUPERGOON_ENGINE_EXPORT ConfigReader
{
private:
    static mINI::INIFile file;
    static mINI::INIStructure structure;

public:
    ConfigReader(const char *ini_file_name);
    ~ConfigReader();
    static std::string &GetValueFromCfg(const char *section, const char *item);
    static int GetValueFromCfgInt(const char *section, const char *item);
    static bool GetValueFromCfgBool(const char *section, const char *item);
};


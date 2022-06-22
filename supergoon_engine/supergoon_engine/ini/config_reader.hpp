#pragma once
#include <supergoon_engine/ini/ini.hpp>
#include <supergoon_engine_export.h>

class ConfigReader
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

mINI::INIFile ConfigReader::file("");
mINI::INIStructure ConfigReader::structure;

ConfigReader::ConfigReader(const char *ini_file_name)
{
    std::string prefix = "./assets/config/";
    auto file_name = prefix + ini_file_name;
    file = mINI::INIFile(file_name);
    file.read(structure);
}

ConfigReader::~ConfigReader()
{
}
std::string &ConfigReader::GetValueFromCfg(const char *section, const char *item)
{
    return structure[section][item];
}
int ConfigReader::GetValueFromCfgInt(const char *section, const char *item)
{
    return stoi(structure[section][item]);
}

bool ConfigReader::GetValueFromCfgBool(const char *section, const char *item)
{
    auto &value = structure[section][item];
    if (value == "0")
        return false;
    return true;
}
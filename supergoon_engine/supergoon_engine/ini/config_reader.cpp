#include <supergoon_engine/ini/config_reader.hpp>

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
#include <supergoon_engine/engine/debug.hpp>
#include <iostream>

void Debug::Log(LogLevel level, const char* thing_to_write)
{
    std::string hi = "\n";
    auto thing = thing_to_write + hi;
    printf(thing.c_str());
}
void Debug::LogWarn(const char *fmt, ...)
{
    va_list args;
    char buf[1000];
    va_start(args, fmt);
    vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);
    Log(LogLevel::Warning, buf);
}
void Debug::LogError(const char *fmt, ...)
{
    va_list args;
    char buf[1000];
    va_start(args, fmt);
    vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);
    Log(LogLevel::Error, buf);
}
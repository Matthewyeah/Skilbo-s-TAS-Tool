// Config.h
#pragma once
#include <vector>
#include <string>
#include <cstdint> 

namespace Config
{
    void Load();
    uintptr_t GetBaseAddress(const char* name);
    std::vector<unsigned int> GetOffsets(const char* name);
}
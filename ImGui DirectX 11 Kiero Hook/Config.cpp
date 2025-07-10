// Config.cpp
#include "Config.h"
#include <Windows.h>
#include <string>
#include <sstream>
#include <map>

namespace Config
{
    static std::map<std::string, std::string> offsets;

    void Load()
    {
        char result[255];
        // We'll read all the keys from the [Offsets] section.
        // Make sure config.ini is in the same directory as the game's .exe
        GetPrivateProfileString("Offsets", "l2Address", "0", result, 255, ".\\config.ini");
        offsets["l2Address"] = result;
        GetPrivateProfileString("Offsets", "r2Address", "0", result, 255, ".\\config.ini");
        offsets["r2Address"] = result;
        GetPrivateProfileString("Offsets", "leftStickAddress", "0", result, 255, ".\\config.ini");
        offsets["leftStickAddress"] = result;
        GetPrivateProfileString("Offsets", "gasAddress", "0", result, 255, ".\\config.ini");
        offsets["gasAddress"] = result;
        GetPrivateProfileString("Offsets", "brakeAddress", "0", result, 255, ".\\config.ini");
        offsets["brakeAddress"] = result;
        GetPrivateProfileString("Offsets", "leanAddress", "0", result, 255, ".\\config.ini");
        offsets["leanAddress"] = result;
    }

    uintptr_t GetBaseAddress(const char* name)
    {
        // Check if the key exists in our map
        if (offsets.find(name) == offsets.end()) return 0;

        const std::string& value_str = offsets.at(name);
        if (value_str.empty()) return 0;

        // Use a try-catch block to prevent crashes from invalid values in the .ini
        try {
            return std::stoul(value_str, nullptr, 16);
        }
        catch (const std::invalid_argument&) {
            return 0;
        }
        catch (const std::out_of_range&) {
            return 0;
        }
    }

    std::vector<unsigned int> GetOffsets(const char* name)
    {
        if (offsets.find(name) == offsets.end()) return {};

        const std::string& value_str = offsets.at(name);
        if (value_str.empty()) return {};

        std::vector<unsigned int> result_offsets;
        std::stringstream ss(value_str);
        std::string item;

        // Skip the first value, as it's the base offset for FindDMAAddy
        std::getline(ss, item, ',');

        while (std::getline(ss, item, ',')) {
            try {
                result_offsets.push_back(std::stoul(item, nullptr, 16));
            }
            catch (...) {
                // If any offset is invalid, return an empty vector to be safe
                return {};
            }
        }
        return result_offsets;
    }
}
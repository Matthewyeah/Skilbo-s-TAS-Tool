// GamePointers.cpp
#include "GamePointers.h"
#include "Config.h"

namespace GamePointers
{
    // --- Variable Definitions ---
    uintptr_t tfModBase = 0;
    uintptr_t gasAddress = 0;
    uintptr_t brakeAddress = 0;
    uintptr_t leanAddress = 0;
    uintptr_t l2Address = 0;
    uintptr_t r2Address = 0;
    uintptr_t leftStickAddress = 0;

    // --- Function Definitions ---

    uintptr_t FindDMAAddy(uintptr_t base, std::vector<unsigned int> offsets)
    {
        uintptr_t addr = base;
        for (unsigned int i = 0; i < offsets.size(); ++i)
        {
            if (*(uintptr_t*)addr == 0) return 0; 
            addr = *(uintptr_t*)addr;
            addr += offsets[i];
        }
        return addr;
    }

    void InitialiseControllerPointers()
    {
        tfModBase = (uintptr_t)GetModuleHandle(NULL);
        if (tfModBase == 0) return;

        l2Address = FindDMAAddy(tfModBase + Config::GetBaseAddress("l2Address"), {});
        r2Address = FindDMAAddy(tfModBase + Config::GetBaseAddress("r2Address"), {});
        leftStickAddress = FindDMAAddy(tfModBase + Config::GetBaseAddress("leftStickAddress"), {});
    }

    void InitialiseInTrackPointers()
    {
        if (tfModBase == 0) return;

        gasAddress = FindDMAAddy(tfModBase + Config::GetBaseAddress("gasAddress"), Config::GetOffsets("gasAddress"));
        brakeAddress = FindDMAAddy(tfModBase + Config::GetBaseAddress("brakeAddress"), Config::GetOffsets("brakeAddress"));
        leanAddress = FindDMAAddy(tfModBase + Config::GetBaseAddress("leanAddress"), Config::GetOffsets("leanAddress"));
    }

    byte GetGasValue() {
        if (gasAddress == 0) return 0;
        return *(byte*)gasAddress;
    }

    void SetGasValue(byte newValue) {
        if (gasAddress == 0) return;
        *(byte*)gasAddress = newValue;
    }

    byte GetBrakeValue() {
        if (brakeAddress == 0) return 0;
        return *(byte*)brakeAddress;
    }

    void SetBrakeValue(byte newValue) {
        if (brakeAddress == 0) return;
        *(byte*)brakeAddress = newValue;
    }

    signed char GetLeanValue() {
        if (leanAddress == 0) return -1;
        return *(signed char*)leanAddress;
    }

    void SetLeanValue(signed char newValue) {
        if (leanAddress == 0) return;
        *(signed char*)leanAddress = newValue;
    }

    byte GetL2Value() {
        if (l2Address == 0) return 0;
        return *(byte*)l2Address;
    }

    void SetL2Value(byte newValue) {
        if (l2Address == 0) return;
        *(byte*)l2Address = newValue;
    }

    byte GetR2Value() {
        if (r2Address == 0) return 0;
        return *(byte*)r2Address;
    }

    void SetR2Value(byte newValue) {
        if (r2Address == 0) return;
        *(byte*)r2Address = newValue;
    }

    signed char GetLeftStickValue() {
        if (leftStickAddress == 0) return -1;
        return *(signed char*)leftStickAddress;
    }

    void SetLeftStickValue(signed char newValue) {
        if (leftStickAddress == 0) return;
        *(signed char*)leftStickAddress = newValue;
    }
}
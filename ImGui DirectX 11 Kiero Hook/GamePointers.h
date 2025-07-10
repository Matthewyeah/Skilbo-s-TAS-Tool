#pragma once
#include <windows.h>
#include <vector>
#include <string>

namespace GamePointers
{
    // --- Stored Addresses ---
    // Module Bases
    uintptr_t tfModBase = 0;
    uintptr_t xiModBase = 0;

    // Final Addresses
    uintptr_t gasAddress = 0;
    uintptr_t brakeAddress = 0;
    uintptr_t leanAddress = 0;
    uintptr_t frameCountAddress = 0;
    uintptr_t timeAddress = 0;
    uintptr_t trackNameAddress = 0;
    uintptr_t l2Address = 0;
    uintptr_t r2Address = 0;
    uintptr_t leftStickAddress = 0; 

    // This function resolves multi-level pointers.
    uintptr_t FindDMAAddy(uintptr_t base, std::vector<unsigned int> offsets)
    {
        uintptr_t addr = base;
        for (unsigned int i = 0; i < offsets.size(); ++i)
        {
            addr = *(uintptr_t*)addr;
            addr += offsets[i];
        }
        return addr;
    }

    // This function finds all our pointers when the DLL is first loaded.
    void InitialiseAddresses()
    {
        // Get and store the module base addresses.
        tfModBase = (uintptr_t)GetModuleHandle(NULL);
        xiModBase = (uintptr_t)GetModuleHandle("XINPUT1_3.dll");

        // Controller Input Addresses
        l2Address = FindDMAAddy(tfModBase + 0x1054D76, {});
        r2Address = FindDMAAddy(tfModBase + 0x1054D77, {});
        leftStickAddress = FindDMAAddy(tfModBase + 0x1054D79, {}); 

        // Bike State Addresses
        gasAddress = FindDMAAddy(tfModBase + 0x104F020, { 0xC, 0x10 });
        brakeAddress = FindDMAAddy(tfModBase + 0x104F020, { 0xC, 0x11 });
        leanAddress = FindDMAAddy(tfModBase + 0x104F020, { 0xC, 0x0 });

        // Game State Addresses
        frameCountAddress = FindDMAAddy(xiModBase + 0x83CAC, {});
        timeAddress = FindDMAAddy(xiModBase + 0x8391C, {});
        trackNameAddress = FindDMAAddy(xiModBase + 0x838B4, {});
    }

    // --- Functions to read/write data directly ---

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

    int GetFrameCount() {
        if (frameCountAddress == 0) return 0;
        return *(int*)frameCountAddress;
    }

    std::string GetTime() {
        if (timeAddress == 0) return "";
        return std::string((char*)timeAddress);
    }

    std::string GetTrackName() {
        if (trackNameAddress == 0) return "";
        return std::string((char*)trackNameAddress);
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

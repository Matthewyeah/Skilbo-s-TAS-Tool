// GamePointers.h
#pragma once
#include <windows.h>
#include <vector>
#include <string>

namespace GamePointers
{
    // --- Variable Declarations ---
    extern uintptr_t tfModBase;

    // Controller pointers (available in menus)
    extern uintptr_t l2Address;
    extern uintptr_t r2Address;
    extern uintptr_t leftStickAddress;

    // In-Track pointers (available after loading a track)
    extern uintptr_t gasAddress;
    extern uintptr_t brakeAddress;
    extern uintptr_t leanAddress;

    // --- Function Declarations ---
    void InitialiseControllerPointers();
    void InitialiseInTrackPointers();
    uintptr_t FindDMAAddy(uintptr_t base, std::vector<unsigned int> offsets);

    byte GetGasValue();
    void SetGasValue(byte newValue);
    byte GetBrakeValue();
    void SetBrakeValue(byte newValue);
    signed char GetLeanValue();
    void SetLeanValue(signed char newValue);
    byte GetL2Value();
    void SetL2Value(byte newValue);
    byte GetR2Value();
    void SetR2Value(byte newValue);
    signed char GetLeftStickValue();
    void SetLeftStickValue(signed char newValue);
}
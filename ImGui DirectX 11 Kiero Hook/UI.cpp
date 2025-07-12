// UI.cpp
#include "imgui.h"
#include "GamePointers.h"
#include "UI.h"
#include <string>
#include <vector>
#include <algorithm>
#include <Windows.h>

// --- UI Helpers ---
std::string GetExecutablePath() {
    char path[MAX_PATH] = { 0 };
    GetModuleFileNameA(NULL, path, MAX_PATH);
    return std::string(path);
}

void TextCentered(const char* text) {
    if (text == nullptr) return;
    auto windowWidth = ImGui::GetWindowSize().x;
    auto textWidth = ImGui::CalcTextSize(text).x;
    ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
    ImGui::TextUnformatted(text);
}

// --- Main UI Rendering ---
void RenderTASMenu(bool& show_menu, bool pointers_initialized)
{
    if (show_menu)
    {
        ImGui::Begin("Skilbo's TAS Tool", &show_menu);

        if (!pointers_initialized)
        {
            ImGui::Text("Pointers not initialized. Waiting for game to load...");
        }
        else
        {
            // -- Collapsible Section 1: Live Values --
            if (ImGui::CollapsingHeader("Live Values", ImGuiTreeNodeFlags_DefaultOpen))
            {
                ImGui::Text("L2: %d", GamePointers::GetL2Value());
                ImGui::Text("R2: %d", GamePointers::GetR2Value());
                ImGui::Text("Left stick: %d", GamePointers::GetLeftStickValue());
                ImGui::Separator();
                if (GamePointers::gasAddress != 0)
                {
                    ImGui::Text("Frame: %d", GamePointers::GetFrameValue());
                    ImGui::Text("Gas: %d", GamePointers::GetGasValue());
                    ImGui::Text("Brake: %d", GamePointers::GetBrakeValue());
                    ImGui::Text("Lean: %d", GamePointers::GetLeanValue());
                }
                else
                {
                    ImGui::TextDisabled("Frame: (N/A - Load a track to initialize)");
                    ImGui::TextDisabled("Gas: (N/A - Load a track to initialize)");
                    ImGui::TextDisabled("Brake: (N/A - Load a track to initialize)");
                    ImGui::TextDisabled("Lean: (N/A - Load a track to initialize)");
                }
            }

            // -- Collapsible Section 2: Addresses & Game Info --
            if (ImGui::CollapsingHeader("Addresses & Game Info"))
            {
                ImGui::Text("Executable Path: %s", GetExecutablePath().c_str());
                ImGui::Text("Trials Fusion Module Base Address: 0x%p", (void*)GamePointers::tfModBase);
                ImGui::Separator();
                ImGui::Text("Gas Address: 0x%p", (void*)GamePointers::gasAddress);
                ImGui::Text("Brake Address: 0x%p", (void*)GamePointers::brakeAddress);
                ImGui::Text("Lean Address: 0x%p", (void*)GamePointers::leanAddress);
                ImGui::Text("L2 Address: 0x%p", (void*)GamePointers::l2Address);
                ImGui::Text("R2 Address: 0x%p", (void*)GamePointers::r2Address);
                ImGui::Text("Left Stick Address: 0x%p", (void*)GamePointers::leftStickAddress);
                ImGui::Text("Frame Address: 0x%p", (void*)GamePointers::frameAddress);
            }

            // -- Collapsible Section 3: Style Editor --
            if (ImGui::CollapsingHeader("Style Editor"))
            {
                // Add a little helper guide
                ImGui::TextWrapped("You can edit the style in real-time. The 'Export' button below will output C++ code to the clipboard that you can paste into a new style function.");
                ImGui::Separator();

                // Show the Style Editor
                ImGui::ShowStyleEditor();
            }
        }
        ImGui::End();
    }
}
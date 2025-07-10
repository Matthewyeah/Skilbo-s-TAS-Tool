// dllmain.cpp
#include "includes.h"
#include <Windows.h>
#include <string> 
#include "GamePointers.h"
#include "Config.h"
#include "UI.h"
#include "TMStyle.h" 

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// D3D11 Hooking
Present oPresent;
HWND window = NULL;
WNDPROC oWndProc;
ID3D11Device* pDevice = NULL;
ID3D11DeviceContext* pContext = NULL;
ID3D11RenderTargetView* mainRenderTargetView;

// Global state variables
bool init = false;
bool show_menu = true;
bool controller_pointers_found = false;
bool in_track_pointers_found = false;

void InitImGui()
{
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    
    ImGui::StyleColorsDark();

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    io.Fonts->Clear();
    io.Fonts->AddFontFromFileTTF("C:\\Program Files (x86)\\Steam\\steamapps\\common\\Trials Fusion\\datapack\\Fonts\\Bahnschrift-Regular.ttf", 20.0f);

    io.FontGlobalScale = 1.0f;
    ImGui_ImplWin32_Init(window);
    ImGui_ImplDX11_Init(pDevice, pContext);
}

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (uMsg == WM_KEYUP) {
        if (wParam == VK_F1) {
            show_menu = !show_menu;
        }
    }
    if (show_menu && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam)) {
        return true;
    }
    return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
    if (!init)
    {
        if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice)))
        {
            pDevice->GetImmediateContext(&pContext);
            DXGI_SWAP_CHAIN_DESC sd;
            pSwapChain->GetDesc(&sd);
            window = sd.OutputWindow;
            ID3D11Texture2D* pBackBuffer;
            pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
            if (pBackBuffer) {
                pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
                pBackBuffer->Release();
            }
            oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
            InitImGui();
            init = true;
        }
        else
        {
            return oPresent(pSwapChain, SyncInterval, Flags);
        }
    }

    if (!controller_pointers_found)
    {
        __try {
            GamePointers::InitialiseControllerPointers();
            if (GamePointers::tfModBase != 0)
                controller_pointers_found = true;
        }
        __except (EXCEPTION_EXECUTE_HANDLER) {}
    }

    if (controller_pointers_found && !in_track_pointers_found)
    {
        __try {
            GamePointers::InitialiseInTrackPointers();
            if (GamePointers::gasAddress != 0)
                in_track_pointers_found = true;
        }
        __except (EXCEPTION_EXECUTE_HANDLER) {}
    }

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    RenderTASMenu(show_menu, controller_pointers_found);

    ImGui::Render();
    pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    return oPresent(pSwapChain, SyncInterval, Flags);
}

DWORD WINAPI MainThread(LPVOID lpReserved)
{
    Sleep(1000);
    Config::Load();

    bool hook_initialized = false;
    do
    {
        if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
        {
            kiero::bind(8, (void**)&oPresent, hkPresent);
            hook_initialized = true;
        }
    } while (!hook_initialized);

    return TRUE;
}

BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved)
{
    switch (dwReason)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hMod);
        CreateThread(nullptr, 0, MainThread, hMod, 0, nullptr);
        break;
    case DLL_PROCESS_DETACH:
        kiero::shutdown();
        break;
    }
    return TRUE;
}
#include "includes.h"
#include <Windows.h>
#include "GamePointers.h" 

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

Present oPresent;
HWND window = NULL;
WNDPROC oWndProc;
ID3D11Device* pDevice = NULL;
ID3D11DeviceContext* pContext = NULL;
ID3D11RenderTargetView* mainRenderTargetView;

bool show_menu = true;
bool pointers_initialized = false;

void TextCentered(const char* text) {
	if (text == nullptr) return;
	auto windowWidth = ImGui::GetWindowSize().x;
	auto textWidth = ImGui::CalcTextSize(text).x;
	ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
	ImGui::TextUnformatted(text);
}

void RenderMyMenu()
{
	if (show_menu)
	{
		ImGui::Begin("Skilbo's TAS Tool");
		ImGui::Text("Press F1 to hide this menu.");
		ImGui::Separator();

		if (pointers_initialized)
		{
			TextCentered("Bike & Controller Values");
			ImGui::Separator();

			// Display gas
			if (GamePointers::gasAddress) {
				byte gas = GamePointers::GetGasValue();
				// ImGui::Text("Gas: 0x%p | Value: %d", (void*)GamePointers::gasAddress, gas);
				ImGui::Text("Gas: %d", gas);
			}

			// Display brake
			if (GamePointers::brakeAddress) {
				byte brake = GamePointers::GetBrakeValue();
				// ImGui::Text("Brake: 0x%p | Value: %d", (void*)GamePointers::brakeAddress, brake);
				ImGui::Text("Brake: %d", brake);
			}

			// Display lean
			if (GamePointers::leanAddress) {
				signed char lean = GamePointers::GetLeanValue();
				// ImGui::Text("Lean: 0x%p | Value: %d", (void*)GamePointers::leanAddress, lean);
				ImGui::Text("Lean: %d", lean);
			}

			ImGui::Separator();

			// Display L2
			if (GamePointers::l2Address) {
				byte l2 = GamePointers::GetL2Value();
				// ImGui::Text("L2: 0x%p | Value: %d", (void*)GamePointers::l2Address, l2);
				ImGui::Text("L2: %d", l2);
			}

			// Display R2
			if (GamePointers::r2Address) {
				byte r2 = GamePointers::GetR2Value();
				// ImGui::Text("R2: 0x%p | Value: %d", (void*)GamePointers::r2Address, r2);
				ImGui::Text("R2: %d", r2);
			}

			// Display left stick
			if (GamePointers::leftStickAddress) {
				signed char leftStick = GamePointers::GetLeftStickValue();
				// ImGui::Text("Left Stick: 0x%p | Value: %d", (void*)GamePointers::leftStickAddress, leftStick);
				ImGui::Text("Left stick: %d", leftStick);
			}
		}
		else
		{
			ImGui::Text("Pointers not initialized.");
		}

		ImGui::End();
	}
}

void InitImGui()
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();

	ImGui::StyleColorsDark();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	// io.Fonts->AddFontFromFileTTF("C:\\Skilbo-s-TAS-Tool\\ImGui DirectX 11 Kiero Hook\\Cascadia.ttf", 16.0f);
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


bool init = false;
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

	if (!pointers_initialized)
	{
		__try
		{
			GamePointers::InitialiseAddresses();
			if (GamePointers::tfModBase != 0)
			{
				pointers_initialized = true;
			}
		}
		__except (EXCEPTION_EXECUTE_HANDLER)
		{
			// Memory not ready yet; try again next frame
		}
	}

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	RenderMyMenu();

	ImGui::Render();
	pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	return oPresent(pSwapChain, SyncInterval, Flags);
}


DWORD WINAPI MainThread(LPVOID lpReserved)
{
	Sleep(1000);

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

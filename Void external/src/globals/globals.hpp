#pragma once
#include <windows.h>
#include <d3d11.h>
#include "../memory/memory.hpp"
#include "../reader/reader.hpp"

namespace g //globals I ain't typing allat
{
	inline bool running = true;
	inline auto mem = Memory{ L"cs2.exe" };
	inline const auto client = mem.GetModuleAddress(L"client.dll");
	inline const auto server = mem.GetModuleAddress(L"server.dll");
	inline const auto engine = mem.GetModuleAddress(L"engine.dll");
	inline const auto screenWidth = GetSystemMetrics(SM_CXSCREEN);
	inline const auto screenHeight = GetSystemMetrics(SM_CYSCREEN);
}

namespace togg //toggles
{
	
}

namespace overlay
{
	inline HWND hWnd = 0;
	inline ID3D11Device* device = nullptr;
	inline ID3D11DeviceContext* context = nullptr;
	inline IDXGISwapChain* swapChain = nullptr;
	inline ID3D11RenderTargetView* targetView = nullptr;
	inline bool renderMenu = false;
}



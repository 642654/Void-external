#include "overlay.hpp"




void InitOverlay()
{

	overlay::hWnd = FindWindowW(L"CEF-OSC-WIDGET", L"NVIDIA GeForce Overlay");
	if (!overlay::hWnd)
	{
		std::cout << "[-] Failed to find the window\n";
		return;
	} 

	MARGINS margins = { -1 };
	margins.cyBottomHeight = margins.cyTopHeight = margins.cxLeftWidth = margins.cxRightWidth = -1;

	if (DwmExtendFrameIntoClientArea(overlay::hWnd, &margins))
	{
		std::cout << "[-] DwmExtendFrameIntoClientArea failed\n";
	}

	if (!SetLayeredWindowAttributes(overlay::hWnd, RGB(0, 0, 0), BYTE(255), LWA_ALPHA))
		std::cout << "[-] SetLayeredWindowAttributes failed\n";

	auto windowExStyles = GetWindowLongW(overlay::hWnd, GWL_EXSTYLE);
	SetWindowLongW(overlay::hWnd, GWL_EXSTYLE, windowExStyles | 0x8L | 0x20L);
	SetWindowPos(overlay::hWnd, HWND_TOPMOST, 0, 0, 0, 0, 0x0002 | 0x0001);


	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));

	sd.BufferCount = 2;

	sd.BufferDesc.Width = 0;
	sd.BufferDesc.Height = 0;

	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;

	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	sd.OutputWindow = overlay::hWnd;

	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;

	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	D3D_FEATURE_LEVEL featureLevel;
	const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };

	HRESULT hr = D3D11CreateDeviceAndSwapChain(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		0U,
		featureLevelArray,
		2U,
		D3D11_SDK_VERSION,
		&sd,
		&overlay::swapChain,
		&overlay::device,
		&featureLevel,
		&overlay::context);

	if (hr != S_OK)
	{
		std::cout << "[-] D3D11CreateDeviceAndSwapChain failed with code " << hr << '\n';
		return;
	}

	ID3D11Texture2D* backBuffer = nullptr;
	if (overlay::swapChain->GetBuffer(0U, IID_PPV_ARGS(&backBuffer)) != S_OK)
	{
		std::cout << "[-] Failed to get the back buffer\n";
		return;
	}

	if (overlay::device->CreateRenderTargetView(backBuffer, nullptr, &overlay::targetView) != S_OK)
	{
		std::cout << "[-] Failed to create a render target view";
		return;
	}
	backBuffer->Release();


	ImGui::CreateContext();
	ImGui::StyleColorsLight();

	if (!ImGui_ImplDX11_Init(overlay::device, overlay::context))
	{
		std::cout << "[-] ImGui_ImplDX11_Init failed\n";
	}
	if (!ImGui_ImplWin32_Init(overlay::hWnd))
	{
		std::cout << "[-] ImGui_ImplWin32_Init failed\n";
	}
}


void BeginRender()
{
	MSG msg;
	while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void Render()
{
	
	ESP();
}

void EndRender()
{
	constexpr float color[4]{ 0, 0, 0, 0 };
	ImGui::Render();
	overlay::context->OMSetRenderTargets(1, &overlay::targetView, NULL);
	overlay::context->ClearRenderTargetView(overlay::targetView, color);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	overlay::swapChain->Present(1, 0);
}

void UninitOverlay()
{
	if (overlay::device)
	{
		overlay::device->Release();
		overlay::context->Release();
		overlay::swapChain->Release();
		overlay::targetView->Release();
	}
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}
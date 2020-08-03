//#include "MyImGUI.h"
//
//
//bool CreateDevice(HWND hWindow)
//{
//	DXGI_SWAP_CHAIN_DESC sd;
//	ZeroMemory(&sd, sizeof(sd));
//	sd.BufferCount = 2;
//	sd.BufferDesc.Width = 0;
//	sd.BufferDesc.Height = 0;
//	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
//	sd.BufferDesc.RefreshRate.Numerator = 60;
//	sd.BufferDesc.RefreshRate.Denominator = 1;
//	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
//	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
//	sd.OutputWindow = hWindow;
//	sd.SampleDesc.Count = 1;
//	sd.SampleDesc.Quality = 0;
//	sd.Windowed = TRUE;
//	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
//
//	UINT createDeviceFlags = 0;
//	D3D_FEATURE_LEVEL featureLevel;
//	const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
//	if (D3D11CreateDeviceAndSwapChain(
//		NULL,
//		D3D_DRIVER_TYPE_HARDWARE,
//		NULL,
//		createDeviceFlags,
//		featureLevelArray,
//		2,
//		D3D11_SDK_VERSION,
//		&sd,
//		&pSwapChain,
//		&pDevice,
//		&featureLevel,
//		&pDeviceContext
//	) != S_OK)
//		return false;
//
//	CreateRenderTarget();
//	return true;
//}
//
//void CleanupDevice()
//{
//	CleanupRenderTarget();
//	if (pSwapChain) { pSwapChain->Release(); pSwapChain = NULL; }
//	if (pDeviceContext) { pDeviceContext->Release(); pDeviceContext = NULL; }
//	if (pDevice) { pDevice->Release(); pDevice = NULL; }
//}
//
//void CreateRenderTarget()
//{
//	ID3D11Texture2D* pBackBuffer;
//	pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
//	pDevice->CreateRenderTargetView(pBackBuffer, NULL, &pRenderTargetView);
//	pBackBuffer->Release();
//}
//
//void CleanupRenderTarget()
//{
//	if (pRenderTargetView)
//	{
//		pRenderTargetView->Release();
//		pRenderTargetView = NULL;
//	}
//}
//
//LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
//LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
//{
//	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
//		return true;
//
//	switch (msg)
//	{
//	case WM_SIZE:
//		if (pDevice != NULL && wParam != SIZE_MINIMIZED)
//		{
//			CleanupRenderTarget();
//			pSwapChain->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);
//			CreateRenderTarget();
//		}
//		return 0;
//	case WM_SYSCOMMAND:
//		if ((wParam & 0xfff0) == SC_KEYMENU)
//			return 0;
//		break;
//	case WM_DESTROY:
//		::PostQuitMessage(0);
//		return 0;
//	}
//	return ::DefWindowProc(hWnd, msg, wParam, lParam);
//}

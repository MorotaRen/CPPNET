#pragma once

#include "imGui/imgui.h"
#include "imGui/imgui_impl_win32.h"
#include "imGui/imgui_impl_dx11.h"

#include "config.h"
#pragma comment(lib, "d3d11.lib")
namespace MyImGui {
	static ID3D11Device*            pDevice = NULL;
	static ID3D11DeviceContext*     pDeviceContext = NULL;
	static IDXGISwapChain*          pSwapChain = NULL;
	static ID3D11RenderTargetView*  pRenderTargetView = NULL;

	HWND hWindow;

	bool show_gui = true;
	bool checkbox;

	static bool CreateDevice(HWND hWindow);
	static void CleanupDevice();
	static void CreateRenderTarget();
	static void CleanupRenderTarget();
	int	Showing();

	static LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
}
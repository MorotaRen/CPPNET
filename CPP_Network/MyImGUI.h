#pragma once

#include "imGui/imgui.h"
#include "imGui/imgui_impl_win32.h"
#include "imGui/imgui_impl_dx11.h"

#include "config.h"
#pragma comment(lib, "d3d11.lib")
namespace MyimGui {
	static ID3D11Device*            pDevice = NULL;
	static ID3D11DeviceContext*     pDeviceContext = NULL;
	static IDXGISwapChain*          pSwapChain = NULL;
	static ID3D11RenderTargetView*  pRenderTargetView = NULL;

	static HWND hWindow;
	static bool show_gui = true;
	static bool checkbox;

	bool CreateDevice(HWND hWindow);
	void CleanupDevice();
	void CreateRenderTarget();
	void CleanupRenderTarget();
	int	Showing();

	static LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
}
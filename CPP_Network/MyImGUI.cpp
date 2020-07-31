#include "MyImGUI.h"
bool MyimGui::CreateDevice(HWND hWindow)
{
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
	sd.OutputWindow = hWindow;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	UINT createDeviceFlags = 0;
	D3D_FEATURE_LEVEL featureLevel;
	const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
	if (D3D11CreateDeviceAndSwapChain(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		createDeviceFlags,
		featureLevelArray,
		2,
		D3D11_SDK_VERSION,
		&sd,
		&pSwapChain,
		&pDevice,
		&featureLevel,
		&pDeviceContext
	) != S_OK)
		return false;

	CreateRenderTarget();
	return true;
}

void MyimGui::CleanupDevice()
{
	CleanupRenderTarget();
	if (pSwapChain) { pSwapChain->Release(); pSwapChain = NULL; }
	if (pDeviceContext) { pDeviceContext->Release(); pDeviceContext = NULL; }
	if (pDevice) { pDevice->Release(); pDevice = NULL; }
}

void MyimGui::CreateRenderTarget()
{
	ID3D11Texture2D* pBackBuffer;
	pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
	pDevice->CreateRenderTargetView(pBackBuffer, NULL, &pRenderTargetView);
	pBackBuffer->Release();
}

void MyimGui::CleanupRenderTarget()
{
	if (pRenderTargetView)
	{
		pRenderTargetView->Release();
		pRenderTargetView = NULL;
	}
}

LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT WINAPI MyimGui::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
		return true;

	switch (msg)
	{
	case WM_SIZE:
		if (pDevice != NULL && wParam != SIZE_MINIMIZED)
		{
			CleanupRenderTarget();
			pSwapChain->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);
			CreateRenderTarget();
		}
		return 0;
	case WM_SYSCOMMAND:
		if ((wParam & 0xfff0) == SC_KEYMENU)
			return 0;
		break;
	case WM_DESTROY:
		::PostQuitMessage(0);
		return 0;
	}
	return ::DefWindowProc(hWnd, msg, wParam, lParam);
}

int MyimGui::Showing()
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = MyimGui::WndProc;
	wc.hInstance = GetModuleHandle(0);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszClassName = L"MyimGui";
	RegisterClassEx(&wc);

	MyimGui::hWindow = CreateWindow(wc.lpszClassName, L"MyimGui", WS_OVERLAPPEDWINDOW, 100, 100, 800, 800, NULL, NULL, wc.hInstance, NULL);

	if (MyimGui::hWindow == NULL)
	{
		std::cout << "ウィンドウの作成に失敗\n";
		UnregisterClass(wc.lpszClassName, wc.hInstance);
		std::exit(1);
	}

	if (!MyimGui::CreateDevice(MyimGui::hWindow))
	{
		std::cout << "デバイスの作成に失敗\n";
		MyimGui::CleanupDevice();
		UnregisterClass(wc.lpszClassName, wc.hInstance);
		std::exit(1);
	}

	ShowWindow(MyimGui::hWindow, SW_SHOW);
	UpdateWindow(MyimGui::hWindow);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsLight();

	if (!ImGui_ImplWin32_Init(MyimGui::hWindow))
	{
		std::cout << "ImGui_ImplWin32_Init failed\n";
		ImGui::DestroyContext();
		UnregisterClass(wc.lpszClassName, wc.hInstance);
		std::exit(1);
	}

	if (!ImGui_ImplDX11_Init(MyimGui::pDevice, MyimGui::pDeviceContext))
	{
		std::cout << "ImGui_ImplDX11_Init failed\n";
		ImGui::DestroyContext();
		UnregisterClass(wc.lpszClassName, wc.hInstance);
		std::exit(1);
	}

	//iniを生成しないように
	io.IniFilename = NULL;
	//日本語フォントに対応
	io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\meiryo.ttc", 18.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());

	float clear_color[4] = { 0.45f, 0.55f, 0.60f, 1.00f };
	float color_picker[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			continue;
		}

		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		/*
		ウィンドウサイズを設定します。
		ImGuiCond_Once により、初回のみ設定されます。
		ImGuiCond_Always で、常に設定することもできます。
		*/
		ImGui::SetNextWindowSize(ImVec2(500, 600), ImGuiCond_Once);

		if (ImGui::Begin("MyimGui TitleBar Text", &show_gui))
		{
			ImGui::Text(u8"今日は天気が良いです");

			//区切り線
			ImGui::Separator();

			ImGui::Text(u8"このように");
			ImGui::SameLine();
			ImGui::Text(u8"同じ行にコンテンツを追加することもできます");

			ImGui::Separator();

			ImGui::Checkbox(u8"チェックボックス", &checkbox);

			ImGui::Separator();

			ImGui::ColorPicker4(u8"カラーピッカー", color_picker);

			//フレームレートを表示
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

			ImGui::End();
		}

		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
		MyimGui::pDeviceContext->OMSetRenderTargets(1, &pRenderTargetView, NULL);
		MyimGui::pSwapChain->Present(1, 0);
		MyimGui::pDeviceContext->ClearRenderTargetView(pRenderTargetView, clear_color);
	}

	//後片付け

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	MyimGui::CleanupDevice();
	DestroyWindow(MyimGui::hWindow);
	UnregisterClass(wc.lpszClassName, wc.hInstance);
}
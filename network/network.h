#pragma once
static ID3D11Device*            pDevice = NULL;
static ID3D11DeviceContext*     pDeviceContext = NULL;
static IDXGISwapChain*          pSwapChain = NULL;
static ID3D11RenderTargetView*  pRenderTargetView = NULL;

static HWND hWindow;
static bool show_gui = true;
static bool checkbox;

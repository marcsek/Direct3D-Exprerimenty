#include "Graphics.h"

#pragma comment(lib, "d3d11.lib")

Graphics::Graphics(HWND hWnd)
{
	DXGI_SWAP_CHAIN_DESC swap_descript = {};
	swap_descript.BufferDesc.Width = 0;
	swap_descript.BufferDesc.Height = 0;
	swap_descript.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	swap_descript.BufferDesc.RefreshRate.Numerator = 0;
	swap_descript.BufferDesc.RefreshRate.Denominator = 0;
	swap_descript.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swap_descript.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swap_descript.SampleDesc.Count = 1;
	swap_descript.SampleDesc.Quality = 0;
	swap_descript.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swap_descript.BufferCount = 1;
	swap_descript.OutputWindow = hWnd;
	swap_descript.Windowed = TRUE;
	swap_descript.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swap_descript.Flags = 0;

	D3D11CreateDeviceAndSwapChain
	(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&swap_descript,
		&pSwapChain,
		&pDevice,
		nullptr,
		&pContext
	);

	ID3D11Resource* pBackBuffer = nullptr;
	pSwapChain->GetBuffer(0, __uuidof(ID3D11Resource), reinterpret_cast<void**>(&pBackBuffer));
	pDevice->CreateRenderTargetView
	(
		pBackBuffer,
		nullptr,
		&pTarget
	);
	pBackBuffer->Release();
}

Graphics::~Graphics()
{
	if(pTarget != nullptr)
	{
		pTarget->Release();
	}
	if (pContext != nullptr)
	{
		pContext->Release();
	}
	if (pSwapChain != nullptr)
	{
		pSwapChain->Release();
	}
	if(pDevice != nullptr)
	{
		pDevice->Release();
	}
}

void Graphics::EndFrame()
{
	pSwapChain->Present(1u, 0u);
}

void Graphics::ClearBuffer(float r, float g, float b) noexcept
{
	const float color[] = { r, g, b, 1.0f };
	pContext->ClearRenderTargetView(pTarget, color);
}

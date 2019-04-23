#include "D3D11/D3D11DynamicRHI.h"
#include "d3d11.h"
#include "EngineGlobal.h"
#include "D3D11/AdapterReader.h"
#include "D3D11/D3D11ViewPort.h"
#include "LogUtil/DXTrace.h"

extern D3D11Texture2D* GetSwapChainSurface(D3D11DynamicRHI* D3DRHI, EPixelFormat PixelFormat, IDXGISwapChain* SwapChain);



RHID3D11ViewPort::RHID3D11ViewPort(class D3D11DynamicRHI* InD3DRHI, HWND InWindowHandle, uint32 InSizeX, uint32 InSizeY, EPixelFormat InPreferredPixelFormat)
	:D3DRHI(InD3DRHI)
	, WindowHandle(InWindowHandle)
	, ViewSizeX(InSizeX)
	, ViewSizeY(InSizeY)
	, PreferredPixelFormat(InPreferredPixelFormat)
{
	int mClientWidth = InD3DRHI->view_width;
	int mClientHeight = InD3DRHI->view_height;
	{
		// 填充DXGI_SWAP_CHAIN_DESC用以描述交换链
		DXGI_SWAP_CHAIN_DESC sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.BufferDesc.Width = mClientWidth;
		sd.BufferDesc.Height = mClientHeight;
		sd.BufferDesc.RefreshRate.Numerator = 60;
		sd.BufferDesc.RefreshRate.Denominator = 1;
		sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;	// 注意此处DXGI_FORMAT_B8G8R8A8_UNORM
		sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		// 是否开启4倍多重采样？
		if (InD3DRHI->mEnable4xMsaa)
		{
			sd.SampleDesc.Count = 4;
			sd.SampleDesc.Quality = InD3DRHI->m4xMsaaQuality - 1;
		}
		else
		{
			sd.SampleDesc.Count = 1;
			sd.SampleDesc.Quality = 0;
		}
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.BufferCount = 1;
		sd.OutputWindow = WindowHandle;
		sd.Windowed = TRUE;
		sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		sd.Flags = 0;
		HR(InD3DRHI->dxgiFactory1->CreateSwapChain(InD3DRHI->md3d11Device.Get(), &sd, InD3DRHI->mdxgiSwapChain.GetAddressOf()));
	}
	// 可以禁止alt+enter全屏
	InD3DRHI->dxgiFactory1->MakeWindowAssociation(WindowHandle, DXGI_MWA_NO_ALT_ENTER | DXGI_MWA_NO_WINDOW_CHANGES);
	BackBuffer = GetSwapChainSurface(D3DRHI, InPreferredPixelFormat, InD3DRHI->mdxgiSwapChain.Get());
}



void * RHID3D11ViewPort::GetNativeSwapChain() const
{
	return D3DRHI->mdxgiSwapChain.Get();
}

void * RHID3D11ViewPort::GetNativeBackBufferTexture() const
{
	return BackBuffer;
}

void * RHID3D11ViewPort::GetNativeBackBufferRT() const
{
	return BackBuffer->GetRenderTargetView();
}


//////////////////////////////////////////////////////////////////////////


void D3D11DynamicRHI::OMViewPort(float view_width, float  view_height)
{
	CD3D11_VIEWPORT viewport(0.0f, 0.0f,
		static_cast<float>(view_width),
		static_cast<float>(view_height));
	this->md3d11DeviceContext->RSSetViewports(1, &viewport);
}



void D3D11DynamicRHI::Present()
{
	this->mdxgiSwapChain->Present(0, NULL);
}


RHIViewPortRef D3D11DynamicRHI::RHICreateViewport(void* WindowHandle, uint32 SizeX, uint32 SizeY, bool bIsFullscreen, EPixelFormat PreferredPixelFormat)
{
	// Use a default pixel format if none was specified	
	if (PreferredPixelFormat == EPixelFormat::PF_Unknown)
	{
		PreferredPixelFormat = EPixelFormat::PF_A2B10G10R10;
	}
	RHIViewPortRef viewPort = new RHID3D11ViewPort(this, (HWND)WindowHandle,SizeX,SizeY, PreferredPixelFormat);
	return viewPort;
}


void D3D11DynamicRHI::RHIResizeViewport(RHIViewPortParamRef Viewport, uint32 SizeX, uint32 SizeY, bool bIsFullscreen)
{

}

void D3D11DynamicRHI::RHIResizeViewport(RHIViewPortParamRef Viewport, uint32 SizeX, uint32 SizeY, bool bIsFullscreen, EPixelFormat PreferredPixelFormat)
{

}
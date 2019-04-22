#include "D3D11/D3D11DynamicRHI.h"
#include "d3d11.h"
#include "EngineGlobal.h"
#include "D3D11/AdapterReader.h"
#include "D3D11/D3D11ViewPort.h"

extern D3D11Texture2D* GetSwapChainSurface(D3D11DynamicRHI* D3DRHI, EPixelFormat PixelFormat, IDXGISwapChain* SwapChain);

void D3D11DynamicRHI::OMViewPort(float view_width,float  view_height)
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


RHID3D11ViewPort::RHID3D11ViewPort(class D3D11DynamicRHI* InD3DRHI, HWND InWindowHandle, uint32 InSizeX, uint32 InSizeY, EPixelFormat InPreferredPixelFormat)
	:D3DRHI(InD3DRHI)
	, WindowHandle(InWindowHandle)
	, ViewSizeX(InSizeX)
	, ViewSizeY(InSizeY)
	, PreferredPixelFormat(InPreferredPixelFormat)
{
	RHID3D11RenderTargetRef vRenderTarget = new RHID3D11RenderTarget();
	HRESULT hr;
	//hr = this->mdxgiSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), 
	//	vRenderTarget->GetTextureNativeAddress()
	//);
	BackBuffer = GetSwapChainSurface(D3DRHI, InPreferredPixelFormat, InD3DRHI->mdxgiSwapChain.Get());
}

void * RHID3D11ViewPort::GetNativeSwapChain() const
{
	return nullptr;
}

void * RHID3D11ViewPort::GetNativeBackBufferTexture() const
{
	return nullptr;
}

void * RHID3D11ViewPort::GetNativeBackBufferRT() const
{
	return nullptr;
}


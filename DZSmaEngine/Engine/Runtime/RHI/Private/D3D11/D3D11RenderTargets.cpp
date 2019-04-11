#include "D3D11/D3D11DynamicRHI.h"
#include "LogUtil/COMException.h"
#include "LogUtil/ErrorLogger.h"


void D3D11DynamicRHI::CreateRenderTarget(D3D11RHIRenderTargetParamRef RenderTargetResource)
{
	HRESULT hr;
	hr = this->mdxgiSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), 
		RenderTargetResource->GetTextureNativeAddress()
	);
	///////////////////////////////------------CreateRenderTargetView------------///////////////////////////////////////////
	hr = this->md3d11Device->CreateRenderTargetView(
		RenderTargetResource->GetBackBuffer(), NULL,
		RenderTargetResource->GetRTNativeAddress()
	);
}

void D3D11DynamicRHI::SetRenderTarget(D3D11RHIRenderTargetParamRef RenderTargetResource)
{
	md3d11RenderTargetView = RenderTargetResource->md3d11RenderTargetView.Get();
}


void D3D11DynamicRHI::ClearRMT(D3D11RHIRenderTargetParamRef RenderTargetResource)
{
	float bgcolor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	this->md3d11DeviceContext->ClearRenderTargetView(this->md3d11RenderTargetView.Get(), bgcolor);
}
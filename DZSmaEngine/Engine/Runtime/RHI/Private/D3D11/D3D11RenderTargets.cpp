#include "D3D11/D3D11DynamicRHI.h"
#include "LogUtil/COMException.h"
#include "LogUtil/ErrorLogger.h"


RHIRenderTargetRef D3D11DynamicRHI::CreateRenderTarget(uint32 width, uint32 height)
{
	RHID3D11RenderTargetRef vRenderTarget = new RHID3D11RenderTarget();
	HRESULT hr;
	hr = this->mdxgiSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), 
		vRenderTarget->GetTextureNativeAddress()
	);
	///////////////////////////////------------CreateRenderTargetView------------///////////////////////////////////////////
	hr = this->md3d11Device->CreateRenderTargetView(
		vRenderTarget->GetBackBuffer(), NULL,
		vRenderTarget->GetRTNativeAddress()
	);
	return vRenderTarget;
}

void D3D11DynamicRHI::SetRenderTarget(RHIRenderTargetParamRef RenderTargetResource)
{
	/*RHID3D11RenderTargetRef vRenderTarget = static_cast<RHID3D11RenderTargetRef>(RenderTargetResource);
	md3d11RenderTargetView = vRenderTarget->md3d11RenderTargetView.Get();*/
}


void D3D11DynamicRHI::ClearRMT(RHIRenderTargetParamRef RenderTargetResource)
{
	RHID3D11RenderTargetRef vRenderTarget = static_cast<RHID3D11RenderTargetRef>(RenderTargetResource);
	float bgcolor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	this->md3d11DeviceContext->ClearRenderTargetView(vRenderTarget->md3d11RenderTargetView.Get(), bgcolor);
}
#include "D3D11/D3D11DynamicRHI.h"
#include "LogUtil/COMException.h"
#include "LogUtil/ErrorLogger.h"


void D3D11DynamicRHI::SetRenderTarget(RHIRenderTargetParamRef RenderTargetResource)
{
	RHID3D11RenderTargetRef vRenderTarget = static_cast<RHID3D11RenderTargetRef>(RenderTargetResource);
	CurrentRenderTargets = vRenderTarget->md3d11RenderTargetView.Get();
}


void D3D11DynamicRHI::ClearRMT()
{
	float bgcolor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	this->md3d11DeviceContext->ClearRenderTargetView(CurrentRenderTargets.Get(), bgcolor);
}

void D3D11DynamicRHI::SetDepthTarget(RHIDepthTargetParamRef DepthTargetParam)
{
	RHID3D11DepthTargetRef DepthTargetResource = static_cast<RHID3D11DepthTargetRef>(DepthTargetParam);
	CurrentDepthStencilTarget = DepthTargetResource->GetDepthView();
}


void D3D11DynamicRHI::ClearDepthView()
{
	this->md3d11DeviceContext->ClearDepthStencilView(CurrentDepthStencilTarget.Get(),
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0
	);
}

void D3D11DynamicRHI::CommitRenderTargetsAndUAVs()
{
	md3d11DeviceContext->OMSetRenderTargets(1,
		CurrentRenderTargets.GetAddressOf(),
		CurrentDepthStencilTarget.Get()
	);
}

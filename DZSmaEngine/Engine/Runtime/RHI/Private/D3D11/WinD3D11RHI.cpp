#include "D3D11/D3D11DynamicRHI.h"

void D3D11DynamicRHI::Tick()
{
	DynamicRHI::Tick();
	BeginDrawViewPort();
	
	EndDrawViewPort();
};

void D3D11DynamicRHI::Exit()
{
	DynamicRHI::Exit();
}


void D3D11DynamicRHI::OMRenderTarget(RHIRenderTargetRef RenTarRef, RHIDepthTargetRef defRef)
{
	RHID3D11RenderTargetRef d3dRenderTar = static_cast<RHID3D11RenderTargetRef>(RenTarRef);
	RHID3D11DepthTargetRef d3dDepthTar = static_cast<RHID3D11DepthTargetRef>(defRef);

	md3d11DeviceContext->OMSetRenderTargets(1, 
		d3dRenderTar->md3d11RenderTargetView.GetAddressOf(), 
		d3dDepthTar->md3d11DepthStencilView.Get()
	);
}
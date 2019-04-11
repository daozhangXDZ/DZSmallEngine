#include "D3D11/D3D11DynamicRHI.h"


void D3D11DynamicRHI::InitRender()
{
	DynamicRHI::InitRender();
};

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

void D3D11DynamicRHI::InitDefaultRes()
{
	mMainRenderTarget = new D3D11RenderTargetResource();
	GDynamicRHI->CreateRenderTarget(mMainRenderTarget);
	
	mMainDepthRes = new D3D11DepthResource();
	GDynamicRHI->CreateDepthTarget(mMainDepthRes);

	GDynamicRHI->SetRenderTarget(mMainRenderTarget);
	GDynamicRHI->SetDepthTarget(mMainDepthRes);
	GDynamicRHI->OMRenderTarget();
}

void D3D11DynamicRHI::OMRenderTarget()
{
	md3d11DeviceContext->OMSetRenderTargets(1, this->md3d11RenderTargetView.GetAddressOf(), this->mDepthStencilView.Get());
}
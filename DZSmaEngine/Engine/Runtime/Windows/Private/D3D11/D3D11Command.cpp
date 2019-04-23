#include "D3D11/D3D11DynamicRHI.h"
#include "LogUtil/COMException.h"
#include "LogUtil/ErrorLogger.h"


RHIDepthTargetRef D3D11DynamicRHI::CreateDepthTarget(EPixelFormat PixelFormat )
{
	//零食加入深度
	Microsoft::WRL::ComPtr<ID3D11Texture2D> mDepthStencilBuffer;
	D3D11_TEXTURE2D_DESC depthStencilDesc;

	depthStencilDesc.Width = 800;
	depthStencilDesc.Height = 600;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

	// 要使用 4X MSAA?
	if (GDynamicRHI->mEnable4xMsaa)
	{
		depthStencilDesc.SampleDesc.Count = 4;
		depthStencilDesc.SampleDesc.Quality = GDynamicRHI->m4xMsaaQuality - 1;
	}
	else
	{
		depthStencilDesc.SampleDesc.Count = 1;
		depthStencilDesc.SampleDesc.Quality = 0;
	}


	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	// 创建深度缓冲区以及深度模板视图
	md3d11Device->CreateTexture2D(&depthStencilDesc, nullptr, mDepthStencilBuffer.GetAddressOf());
	md3d11Device->CreateDepthStencilView(mDepthStencilBuffer.Get(), nullptr, CurrentDepthStencilTarget.GetAddressOf());
	RHID3D11Texture2D* NewTexture = new RHID3D11Texture2D(
		this,
		mDepthStencilBuffer.Get(),
		nullptr,
		NULL,
		CurrentDepthStencilTarget.Get(),
		depthStencilDesc.Width,
		depthStencilDesc.Height,
		1,
		1,
		PixelFormat,
		"DepthBuffer"
	);
	RHITextureParamRef vTb = NewTexture;
	RHIDepthTargetParamRef DepthView = new RHIDepthTarget(vTb);
	return DepthView;
}

void D3D11DynamicRHI::SetRenderTarget(RHIRenderTargetParamRef RenderTargetResource, RHIDepthTargetParamRef DepthTargetParam)
{
	ID3D11RenderTargetView* RenderTargetView = NULL;
	ID3D11DepthStencilView* depthView = NULL;
	if (RenderTargetResource != nullptr && RenderTargetResource->Texture != nullptr)
	{
		D3D11TextureBase* NewRenderTarget = GetD3D11TextureFromRHITexture(RenderTargetResource->Texture);
		RenderTargetView = NewRenderTarget->GetRenderTargetView();
		CurrentRenderTargets = RenderTargetView;

		
	}
	if (DepthTargetParam != nullptr && DepthTargetParam->Texture != nullptr)
	{
		D3D11TextureBase* NewDepthTarget = GetD3D11TextureFromRHITexture(DepthTargetParam ? DepthTargetParam->Texture : nullptr);
		depthView = NewDepthTarget->GetDepthStencilView();
		CurrentDepthStencilTarget = depthView;
	}
	
}


void D3D11DynamicRHI::ClearRMT()
{
	if (CurrentRenderTargets != nullptr && CurrentRenderTargets.Get() != nullptr)
	{
		float bgcolor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		this->md3d11DeviceContext->ClearRenderTargetView(CurrentRenderTargets.Get(), bgcolor);
	}
}

void D3D11DynamicRHI::ClearDepthView()
{
	if (CurrentDepthStencilTarget != nullptr && CurrentDepthStencilTarget.Get() != nullptr)
	{
		this->md3d11DeviceContext->ClearDepthStencilView(CurrentDepthStencilTarget.Get(),
			D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0
		);
	}
}

void D3D11DynamicRHI::CommitRenderTargetsAndUAVs()
{
	md3d11DeviceContext->OMSetRenderTargets(1,
		CurrentRenderTargets.GetAddressOf(),
		CurrentDepthStencilTarget.Get()
	);
}

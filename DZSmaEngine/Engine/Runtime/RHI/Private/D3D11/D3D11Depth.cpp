#include "D3D11/D3D11DynamicRHI.h"
#include "LogUtil/COMException.h"
#include "LogUtil/ErrorLogger.h"

void D3D11DynamicRHI::CreateDepthTarget(D3D11DepthResourceParamRef DepthTargetResource)
{
	HRESULT hr;
	CD3D11_TEXTURE2D_DESC depthStencilTextureDesc(DXGI_FORMAT_D24_UNORM_S8_UINT, this->view_width, this->view_height);
	depthStencilTextureDesc.MipLevels = 1;
	depthStencilTextureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	
	hr = this->md3d11Device->CreateTexture2D(&depthStencilTextureDesc, NULL, 
		(ID3D11Texture2D**)DepthTargetResource->GetTextureNativeAddress());

	hr = this->md3d11Device->CreateDepthStencilView(
		DepthTargetResource->GetDepthBuffer(), NULL,
		(ID3D11DepthStencilView**)DepthTargetResource->GetDepthViewNativeAddress()
	);
}

void D3D11DynamicRHI::SetDepthTarget(D3D11DepthResourceParamRef DepthTargetResource)
{
	mDepthStencilView = DepthTargetResource->GetDepthView();
}

void D3D11DynamicRHI::ClearDepthView(D3D11DepthResourceParamRef DepthTargetResource)
{
	this->md3d11DeviceContext->ClearDepthStencilView(DepthTargetResource->GetDepthView(),
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0
	);
}
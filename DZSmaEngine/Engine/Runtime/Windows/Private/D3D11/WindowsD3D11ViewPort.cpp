#include "D3D11/D3D11ViewPort.h"
#include "LogUtil/DXTrace.h"
#include <d2d1.h>
#include <dwrite.h>
#include <d3d11_1.h>
#include <wrl/client.h>

D3D11Texture2D* GetSwapChainSurface(D3D11DynamicRHI* D3DRHI, EPixelFormat PixelFormat, IDXGISwapChain* SwapChain)
{
	Microsoft::WRL::ComPtr<ID3D11Texture2D> BackBufferResource;
	SwapChain->GetBuffer(0, IID_ID3D11Texture2D, (void**)BackBufferResource.GetAddressOf());

	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> BackBufferRenderTargetView;
	D3D11_RENDER_TARGET_VIEW_DESC RTVDesc;
	RTVDesc.Format = DXGI_FORMAT_UNKNOWN;
	RTVDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	RTVDesc.Texture2D.MipSlice = 0;
	D3DRHI->md3d11Device->CreateRenderTargetView(BackBufferResource.Get(), &RTVDesc, BackBufferRenderTargetView.GetAddressOf());

	D3D11_TEXTURE2D_DESC TextureDesc;
	BackBufferResource->GetDesc(&TextureDesc);

	// create a shader resource view to allow using the backbuffer as a texture
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> BackBufferShaderResourceView;
	D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc;
	SRVDesc.Format = DXGI_FORMAT_UNKNOWN;
	SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	SRVDesc.Texture2D.MostDetailedMip = 0;
	SRVDesc.Texture2D.MipLevels = 1;
	D3DRHI->md3d11Device->CreateShaderResourceView(BackBufferResource.Get(), &SRVDesc, BackBufferShaderResourceView.GetAddressOf());

	D3D11Texture2D* NewTexture = new D3D11Texture2D(
		D3DRHI,
		BackBufferResource.Get(),
		BackBufferShaderResourceView.Get(),
		BackBufferRenderTargetView.Get(),
		NULL,
		TextureDesc.Width,
		TextureDesc.Height,
		1,
		1,
		PixelFormat,
		"BackBuffer"
	);
	return NewTexture;
}

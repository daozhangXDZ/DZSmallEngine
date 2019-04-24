#include "D3D11/D3D11DynamicRHI.h"

RHITexture2DRef D3D11DynamicRHI::RHICreateTexture2D(uint32 SizeX, uint32 SizeY, uint8 Format, uint32 NumMips, uint32 NumSamples, uint32 Flags)
{
	Microsoft::WRL::ComPtr<ID3D11Texture2D> vTextureResource;
	D3D11_TEXTURE2D_DESC textureDesc;
	HRESULT result;
	D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
	D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;


	// Initialize the render target texture description.
	ZeroMemory(&textureDesc, sizeof(textureDesc));

	// Setup the render target texture description.
	textureDesc.Width = SizeX;
	textureDesc.Height = SizeY;
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	//TODO¸ñÊ½
	textureDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0;

	// Create the render target texture.
	result = md3d11Device->CreateTexture2D(&textureDesc, NULL, vTextureResource.GetAddressOf());
	RHID3D11Texture2D* NewTexture = new RHID3D11Texture2D(
		this,
		vTextureResource.Get(),
		nullptr,
		NULL,
		NULL,
		SizeX,
		SizeY,
		1,
		1,
		EPixelFormat::PF_R32G32B32A32_UINT,
		"NormalTexture"
	);
	return NewTexture;
}
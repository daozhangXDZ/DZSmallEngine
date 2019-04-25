#include "D3D11/D3D11DynamicRHI.h"

RHITexture2DRef D3D11DynamicRHI::RHICreateTexture2D(uint32 SizeX, uint32 SizeY, uint8 Format, uint32 NumMips, uint32 NumSamples, uint32 Flags)
{
	Microsoft::WRL::ComPtr<ID3D11Texture2D> vTextureResource;
	D3D11_TEXTURE2D_DESC textureDesc;
	HRESULT result;
	D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
	D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;
	ZeroMemory(&textureDesc, sizeof(textureDesc));

	//默认视图
	D3D11_DSV_DIMENSION DepthStencilViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	D3D11_RTV_DIMENSION RenderTargetViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	D3D11_SRV_DIMENSION ShaderResourceViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	//是否带SRGB(伽马灰度)
	const bool bSRGB = (Flags & TexCreate_SRGB) != 0;
	const DXGI_FORMAT PlatformResourceFormat = (DXGI_FORMAT)GPixelFormats[Format].PlatformFormat;
	const DXGI_FORMAT PlatformShaderResourceFormat = FindShaderResourceDXGIFormat(PlatformResourceFormat, bSRGB);
	const DXGI_FORMAT PlatformRenderTargetFormat = FindShaderResourceDXGIFormat(PlatformResourceFormat, bSRGB);
	//默认绑定了Shader资源
	uint32 CPUAccessFlags = 0;
	D3D11_USAGE TextureUsage = D3D11_USAGE_DEFAULT;
	uint32 BindFlags = D3D11_BIND_SHADER_RESOURCE;

	bool bCreateRTV = false;
	bool bCreateDSV = false;
	bool bCreateShaderResource = true;

	if (Flags & TexCreate_CPUReadback)
	{
		CPUAccessFlags = D3D11_CPU_ACCESS_READ;
		TextureUsage = D3D11_USAGE_STAGING;
		BindFlags = 0;
		bCreateShaderResource = false;
	}

	// Setup the render target texture description.
	textureDesc.Width = SizeX;
	textureDesc.Height = SizeY;
	textureDesc.MipLevels = NumMips;
	textureDesc.ArraySize = 1;
	//TODO格式
	textureDesc.Format = PlatformResourceFormat;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = BindFlags;
	textureDesc.CPUAccessFlags = CPUAccessFlags;
	textureDesc.MiscFlags = 0;



	//根据FLAG

	if (Flags & TexCreate_RenderTargetable)
	{
		textureDesc.BindFlags |= D3D11_BIND_RENDER_TARGET;
		bCreateRTV = true;
	}
	else if (Flags & TexCreate_DepthStencilTargetable)
	{
		textureDesc.BindFlags |= D3D11_BIND_DEPTH_STENCIL;
		bCreateDSV = true;
	}
	else if (Flags & TexCreate_ResolveTargetable)
	{
		if (Format == PF_DepthStencil || Format == PF_ShadowDepth || Format == PF_D24)
		{
			textureDesc.BindFlags |= D3D11_BIND_DEPTH_STENCIL;
			bCreateDSV = true;
		}
		else
		{
			textureDesc.BindFlags |= D3D11_BIND_RENDER_TARGET;
			bCreateRTV = true;
		}
	}


	
	result = md3d11Device->CreateTexture2D(&textureDesc, NULL, vTextureResource.GetAddressOf());
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> vRenderTargetView = nullptr;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> vDepthStenCilTarget = nullptr;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> vShaderResourceView = nullptr;
	if (bCreateRTV)
	{
		// 创建渲染目标
		
		D3D11_RENDER_TARGET_VIEW_DESC RTVDesc;
		ZeroMemory(&RTVDesc, sizeof(RTVDesc));

		RTVDesc.Format = PlatformRenderTargetFormat;
		RTVDesc.ViewDimension = RenderTargetViewDimension;
		RTVDesc.Texture2D.MipSlice = 0;
		result = md3d11Device->CreateRenderTargetView(vTextureResource.Get(), &RTVDesc, vRenderTargetView.GetAddressOf());
	}
	if (bCreateDSV)
	{
		// 创建深度目标
		
		D3D11_DEPTH_STENCIL_VIEW_DESC DSVDesc;
		ZeroMemory(&DSVDesc, sizeof(DSVDesc));

		DSVDesc.Format = FindDepthStencilDXGIFormat(PlatformResourceFormat);
		result = md3d11Device->CreateDepthStencilView(vTextureResource.Get(), nullptr, vDepthStenCilTarget.GetAddressOf());
	}

	if (bCreateShaderResource)
	{
		
		D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc;
		ZeroMemory(&SRVDesc, sizeof(SRVDesc));

		SRVDesc.Format = PlatformShaderResourceFormat;
		SRVDesc.ViewDimension = ShaderResourceViewDimension;
		SRVDesc.Texture2D.MostDetailedMip = 0;
		SRVDesc.Texture2D.MipLevels = NumMips;
		result = md3d11Device->CreateShaderResourceView(vTextureResource.Get(), &SRVDesc, vShaderResourceView.GetAddressOf());
	}


	RHID3D11Texture2D* NewTexture = new RHID3D11Texture2D(
		this,
		vTextureResource.Get(),
		vShaderResourceView.Get(),
		vRenderTargetView.Get(),
		vDepthStenCilTarget.Get(),
		SizeX,
		SizeY,
		1,
		1,
		EPixelFormat::PF_R32G32B32A32_UINT,
		"NormalTexture"
	);
	return NewTexture;
}
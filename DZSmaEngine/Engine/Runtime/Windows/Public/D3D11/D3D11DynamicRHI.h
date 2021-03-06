#pragma once
#include "DynamicRHI.h"
#include <wrl/client.h>
#include <d3d11.h>
#include <DirectXMath.h>
#include "EngineGlobal.h"
#include "D3D11RHIResources.h"
#include "D3D11State.h"

using namespace DirectX;

/// <summary>
/// DX渲染口
/// </summary>
/// <seealso cref="DynamicRHI" />
class D3D11DynamicRHI : public DynamicRHI
{
public:
	virtual void Tick() override;
	virtual void Exit() override;

protected:	
	/// <summary>
	/// 开启DX设备和交换链
	/// </summary>
	virtual void InitRenderDevice() override;
	

public:
	template<typename TRHIType>
	static FORCEINLINE typename TD3D11ResourceTraits<TRHIType>::TConcreteType* ResourceCast(TRHIType* Resource)
	{
		return static_cast<typename TD3D11ResourceTraits<TRHIType>::TConcreteType*>(Resource);
	}

	virtual RHIViewPortRef RHICreateViewport(void* WindowHandle, uint32 SizeX, uint32 SizeY, bool bIsFullscreen, EPixelFormat PreferredPixelFormat) final override;
	virtual void RHIResizeViewport(RHIViewPortParamRef Viewport, uint32 SizeX, uint32 SizeY, bool bIsFullscreen) final override;
	virtual void RHIResizeViewport(RHIViewPortParamRef Viewport, uint32 SizeX, uint32 SizeY, bool bIsFullscreen, EPixelFormat PreferredPixelFormat) final override;
	virtual void BeginDrawViewPort(RHIViewPortParamRef ViewportRHI, RHITextureParamRef RenderTarget) override;
	virtual void EndDrawViewPort(RHIViewPortParamRef ViewportRHI, bool bPresent, bool bLockToVsync) override;
	/// <summary>
	/// 设置渲染目标
	/// </summary>
	virtual void SetRenderTarget(RHIRenderTargetParamRef RenderTargetResource, RHIDepthTargetParamRef DepthTargetParam) override;
	virtual RHITexture2DParamRef GetRenderTarget(int32 SizeX, int32 SizeY, EPixelFormat PixelFormat) override;
	/// <summary>
	/// 分配渲染目标
	/// </summary>
	virtual void CommitRenderTargetsAndUAVs() override;

	/// <summary>
	/// 清理RenderTarget
	/// </summary>
	virtual void ClearRMT() override;
	/// <summary>
	/// Clears the depth view.
	/// </summary>
	/// <param name="DepthTargetResource">The depth target resource.</param>
	virtual void ClearDepthView() override;
	
	/// <summary>
	/// 分配视口
	/// </summary>
	virtual void OMViewPort(float view_width, float  view_height) override;

	virtual RHIBlendStateRef CreateBlendState() override;
	virtual RHIDepthStencilStateRef CreateDepthStencilState() override;
	virtual RHIRasterizerStateRef CreaRasterizerState() override;
	virtual RHISampleStateRef CreaTextureSampleState() override;
	
	

	//////////////////////////////////状态分配////////////////////////////////////////
	virtual void SetPrimitiveTology(PrimitiveTopology pDrawType) override;
	
	
	//////////////////////////////////状态分配////////////////////////////////////////
	/// <summary>
	/// Sets the state of the rasterizer.
	/// </summary>
	/// <param name="rasterizerStateParam">The rasterizer state parameter.</param>
	virtual void SetRasterizerState(RHIRasterizerStateParamRef rasterizerStateParam) override;
	virtual void SetDepthState(RHIDepthStencilStateParamRef depthStateParam) override;
	virtual void SetBlendState(RHIBlendStateParamRef blendStateParam) override;




	//////////////////////////////////纹理采样模式分配////////////////////////////////////////
	virtual void SetTextureSample(RHISampleStateParamRef TextureSamParam) override;



	
	//////////////////////////////////Shader分配////////////////////////////////////////
	virtual RHIVertexShaderRef CreateVertexShader(FWString shaderFileName) override;
	virtual RHIPixelShaderRef CreatePixelShader(FWString shaderFileName) override;
	virtual RHIVertexLayoutRef CreateInputLayout(RHIVertexInputElementParamRef ResTarget, RHIVertexShaderParamRef vertexShader) override;


	/// <summary>
	/// Omvses the shader.
	/// </summary>
	virtual void OMVSShader(RHIVertexShaderParamRef ResTarget) override;
	
	/// <summary>
	/// Ompses the shader.
	/// </summary>
	virtual void OMPSShader(RHIPixelShaderParamRef ResTarget) override;
	/// <summary>
	/// Ompses the shader.
	/// </summary>
	virtual void OMPInputLayout(RHIVertexLayoutParamRef ResTarget) override;


	/**
	 * 创建着色器资源视图
	 */
	virtual RHIShaderResourceViewRef CreateShaderResourcesView(FWString mainTextureFilePath, ETextureSrcFormat srcFormat) override;
	/**
	 * 设置着色器资源视图
	 */
	virtual void SetShaderRessourcesView(int stIndex, int num, RHIShaderResourceViewParamRef ResTarget, EShaderFrequency bindShaderType)override;
	virtual void SetShaderRessourcesView(int stIndex, int num, void* NativeShaderResourceView, EShaderFrequency bindShaderType)override;

	virtual RHIVertexBufferRef CreateVertexBuffer(void*data, UINT descSize, UINT numVertices)override;
	virtual RHIIndexBufferRef CreateIndexBuffer(DWORD * pMemData, UINT numIndices) override;

	virtual void BindVertexBuffer(RHIVertexBufferParamRef ResTarget, int statIndex, int Num, UINT offset) override;
	virtual void BindIndexBuffer(RHIIndexBufferParamRef ResTarget, int statIndex, DXGI_FORMAT pformat) override;

	virtual void DrawIndexBuffer(RHIIndexBufferParamRef ResTarget, int startIndexPos, int startIndexVertex) override;
	/**
	 * 呈现
	 */
	virtual void Present() override;

	virtual void ApplyConstantBuffer(RHIUniFormBufferRef ResTarget, void * pData, bool isReBind) override;

	/**
	 * 创建缓冲区
	 */
	virtual RHIUniFormBufferRef CreateUniFormBuffer(void* Content, UniFormLayout* layout) final override;
	/**
	 * 设置顶点缓冲区
	 */
	virtual void SetUniFormBuffer(RHIVertexShaderRef shader, RHIUniFormBufferParamRef ResTarget, UINT BufferIndex) final override;
	virtual void SetUniFormBuffer(RHIComputerShader shader, RHIUniFormBufferParamRef ResTarget, UINT BufferIndex)  final override;
	virtual void SetUniFormBuffer(RHIPixelShaderRef shader, RHIUniFormBufferParamRef ResTarget, UINT BufferIndex)	final override;


	////////////////////////////////纹理//////////////////////////////////////////
	virtual RHITexture2DRef CreateTexture2D(uint32 SizeX, uint32 SizeY, uint8 Format, uint32 NumMips, uint32 NumSamples, uint32 Flags) final override;


public:
	virtual RHIDepthTargetRef CreateDepthTarget(EPixelFormat PixelFormat) final override;
	static DXGI_FORMAT GetPlatformTextureResourceFormat(DXGI_FORMAT InFormat, uint32 InFlags);

public:
	Microsoft::WRL::ComPtr< ID3D11Device >				md3d11Device = nullptr;
	Microsoft::WRL::ComPtr< ID3D11DeviceContext >		md3d11DeviceContext = nullptr;
	Microsoft::WRL::ComPtr < IDXGISwapChain	>			mdxgiSwapChain = nullptr;
	Microsoft::WRL::ComPtr<IDXGIFactory1>				dxgiFactory1 = nullptr;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView>		CurrentRenderTargets;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView>		CurrentDepthStencilTarget;

};


/** Find an appropriate DXGI format for the input format and SRGB setting. */
inline DXGI_FORMAT FindShaderResourceDXGIFormat(DXGI_FORMAT InFormat, bool bSRGB)
{
	if (bSRGB)
	{
		switch (InFormat)
		{
		case DXGI_FORMAT_B8G8R8A8_TYPELESS:    return DXGI_FORMAT_B8G8R8A8_UNORM_SRGB;
		case DXGI_FORMAT_R8G8B8A8_TYPELESS:    return DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
		case DXGI_FORMAT_BC1_TYPELESS:         return DXGI_FORMAT_BC1_UNORM_SRGB;
		case DXGI_FORMAT_BC2_TYPELESS:         return DXGI_FORMAT_BC2_UNORM_SRGB;
		case DXGI_FORMAT_BC3_TYPELESS:         return DXGI_FORMAT_BC3_UNORM_SRGB;
		case DXGI_FORMAT_BC7_TYPELESS:         return DXGI_FORMAT_BC7_UNORM_SRGB;
		};
	}
	else
	{
		switch (InFormat)
		{
		case DXGI_FORMAT_B8G8R8A8_TYPELESS: return DXGI_FORMAT_B8G8R8A8_UNORM;
		case DXGI_FORMAT_R8G8B8A8_TYPELESS: return DXGI_FORMAT_R8G8B8A8_UNORM;
		case DXGI_FORMAT_BC1_TYPELESS:      return DXGI_FORMAT_BC1_UNORM;
		case DXGI_FORMAT_BC2_TYPELESS:      return DXGI_FORMAT_BC2_UNORM;
		case DXGI_FORMAT_BC3_TYPELESS:      return DXGI_FORMAT_BC3_UNORM;
		case DXGI_FORMAT_BC7_TYPELESS:      return DXGI_FORMAT_BC7_UNORM;
		};
	}
	switch (InFormat)
	{
	case DXGI_FORMAT_R24G8_TYPELESS: return DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
	case DXGI_FORMAT_R32_TYPELESS: return DXGI_FORMAT_R32_FLOAT;
	case DXGI_FORMAT_R16_TYPELESS: return DXGI_FORMAT_R16_UNORM;
	}
	return InFormat;
}


/** Find the appropriate depth-stencil targetable DXGI format for the given format. */
inline DXGI_FORMAT FindDepthStencilDXGIFormat(DXGI_FORMAT InFormat)
{
	switch (InFormat)
	{
	case DXGI_FORMAT_R24G8_TYPELESS:
		return DXGI_FORMAT_D24_UNORM_S8_UINT; //这是最常用的深度格式
	case DXGI_FORMAT_R32_TYPELESS:
		return DXGI_FORMAT_D32_FLOAT;
	case DXGI_FORMAT_R16_TYPELESS:
		return DXGI_FORMAT_D16_UNORM;
	};
	return InFormat;
}




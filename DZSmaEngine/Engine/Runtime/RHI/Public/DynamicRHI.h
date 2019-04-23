#pragma once
#include <wrl/client.h>
#include <d3d11.h>
#include <DirectXMath.h>
#include "D3D11/D3D11RHIResources.h"
#include "ViewPortDesc.h"
#include "VertexElementDesc.h"
#include "ConstantBufferTypes.h"
#include "RHIDefine.h"
#include "RHIState.h"

class DynamicRHI
{
public:
	void InitRender()
	{
		InitRenderDevice();
	}


	virtual void Tick()
	{

	};
	virtual void Exit()
	{

	};


protected:
	virtual void InitRenderDevice() = 0;
	virtual void BeginDrawViewPort() = 0;
	virtual void EndDrawViewPort() = 0;

public:

	virtual RHIViewPortRef RHICreateViewport(void* WindowHandle, uint32 SizeX, uint32 SizeY, bool bIsFullscreen, EPixelFormat PreferredPixelFormat) =0;
	virtual void RHIResizeViewport(RHIViewPortParamRef Viewport, uint32 SizeX, uint32 SizeY, bool bIsFullscreen) = 0;
	virtual void RHIResizeViewport(RHIViewPortParamRef Viewport, uint32 SizeX, uint32 SizeY, bool bIsFullscreen, EPixelFormat PreferredPixelFormat) = 0;

	//////////////////////////////////////////////////////////////////////////
		
	/// <summary>
	/// Sets the render target.
	/// </summary>
	/// <param name="RenderTargetResource">The render target resource.</param>
	virtual void SetRenderTarget(RHIRenderTargetParamRef RenderTargetResource) = 0;
	virtual void SetDepthTarget(RHIDepthTargetParamRef DepthTargetResource) = 0;
	/// <summary>
	/// 分配渲染目标
	/// </summary>
	virtual void CommitRenderTargetsAndUAVs() = 0;

	/// <summary>
	/// 清理RenderTarget
	/// </summary>
	virtual void ClearRMT() = 0;
	/// <summary>
	/// Clears the depth view.
	/// </summary>
	/// <param name="DepthTargetResource">The depth target resource.</param>
	virtual void ClearDepthView() = 0;

	/// <summary>
	/// 分配视口
	/// </summary>
	virtual void OMViewPort(float view_width, float  view_height) = 0;

	virtual RHIBlendStateRef CreateBlendState() = 0;
	virtual RHIDepthStencilStateRef CreateDepthStencilState() = 0;
	virtual RHIRasterizerStateRef CreaRasterizerState() = 0;
	virtual RHISampleStateRef CreaTextureSampleState() = 0;

	//////////////////////////////////状态分配////////////////////////////////////////
	virtual void SetPrimitiveTology(PrimitiveTopology pDrawType) = 0;


	//////////////////////////////////状态分配////////////////////////////////////////
	/// <summary>
	/// Sets the state of the rasterizer.
	/// </summary>
	/// <param name="rasterizerStateParam">The rasterizer state parameter.</param>
	virtual void SetRasterizerState(RHIRasterizerStateParamRef rasterizerStateParam) = 0;
	virtual void SetDepthState(RHIDepthStencilStateParamRef depthStateParam) = 0;
	virtual void SetBlendState(RHIBlendStateParamRef blendStateParam) = 0;




	//////////////////////////////////纹理采样模式分配////////////////////////////////////////
	virtual void SetTextureSample(RHISampleStateParamRef TextureSamParam) = 0;




	//////////////////////////////////Shader分配////////////////////////////////////////
	virtual RHIVertexShaderRef CreateVertexShader(FWString shaderFileName) = 0;
	virtual RHIPixelShaderRef CreatePixelShader(FWString shaderFileName) = 0;
	virtual RHIVertexLayoutRef CreateInputLayout(RHIVertexInputElementParamRef ResTarget, RHIVertexShaderParamRef vertexShader) = 0;


	/// <summary>
	/// Omvses the shader.
	/// </summary>
	virtual void OMVSShader(RHIVertexShaderParamRef ResTarget) = 0;

	/// <summary>
	/// Ompses the shader.
	/// </summary>
	virtual void OMPSShader(RHIPixelShaderParamRef ResTarget) = 0;
	/// <summary>
	/// Ompses the shader.
	/// </summary>
	virtual void OMPInputLayout(RHIVertexLayoutRef ResTarget) = 0;


	/**
	 * 创建着色器资源视图
	 */
	virtual RHIShaderResourceViewRef CreateShaderResourcesView(FWString mainTextureFilePath, ETextureSrcFormat srcFormat) = 0;
	/**
	 * 设置着色器资源视图
	 */
	virtual void SetShaderRessourcesView(int stIndex, int num, RHIShaderResourceViewParamRef ResTarget, EShaderFrequency bindShaderType) = 0;


	virtual RHIVertexBufferRef CreateVertexBuffer(void*data, UINT descSize, UINT numVertices) = 0;
	virtual RHIIndexBufferRef CreateIndexBuffer(DWORD * pMemData, UINT numIndices) = 0;

	virtual void BindVertexBuffer(RHIVertexBufferParamRef ResTarget, int statIndex, int Num, UINT offset) = 0;
	virtual void BindIndexBuffer(RHIIndexBufferParamRef ResTarget, int statIndex, DXGI_FORMAT pformat) = 0;

	virtual void DrawIndexBuffer(RHIIndexBufferParamRef ResTarget, int startIndexPos, int startIndexVertex) = 0;

	/**
	 * 呈现
	 */
	virtual void Present() = 0;


	virtual void ApplyConstantBuffer(RHIUniFormBufferRef ResTarget, void * Content, bool isReBind) = 0;


	//virtual RHIUniFormBufferRef CreateConstantBuffer(D3D11UniFormBufferRef ResTarget, UINT pDataWidth) =0;
	/**
	 * 创建缓冲区
	 */
	virtual RHIUniFormBufferRef CreateUniFormBuffer(void* Content, UniFormLayout* layout) = 0;
	/**
	 * 设置顶点缓冲区
	 */
	virtual void SetUniFormBuffer(RHIVertexShaderRef shader, RHIUniFormBufferParamRef ResTarget, UINT BufferIndex) = 0;
	virtual void SetUniFormBuffer(RHIComputerShader shader, RHIUniFormBufferParamRef ResTarget, UINT BufferIndex) = 0;
	virtual void SetUniFormBuffer(RHIPixelShaderRef shader, RHIUniFormBufferParamRef ResTarget, UINT BufferIndex) = 0;

public:
	int view_width = 800;
	int view_height = 600;
	ViewPortDesc	mViewPortDesc;
	UINT			m4xMsaaQuality;
	bool			mEnable4xMsaa;
};
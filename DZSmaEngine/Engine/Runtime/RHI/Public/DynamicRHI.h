#pragma once
#include <wrl/client.h>
#include <d3d11.h>
#include <DirectXMath.h>
#include "D3D11/D3D11RHIResources.h"
#include "ViewPortDesc.h"
#include "VertexElementDesc.h"
#include "ConstantBufferTypes.h"

class DynamicRHI
{
public:
	virtual void InitRender()
	{
		InitRenderDevice();
		InitDefaultRes();
		InitContantBuffer();
		InitDefaultState();
		InitShader();
		InitializeViewPort();
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
	/// <summary>
	/// 创建渲染目标
	/// </summary>
	virtual void CreateRenderTarget(D3D11RHIRenderTargetParamRef RenderTargetResource) = 0;
	virtual void SetRenderTarget(D3D11RHIRenderTargetParamRef RenderTargetResource) = 0;


	virtual void CreateDepthTarget(D3D11DepthResourceParamRef DepthTargetResource) = 0;
	virtual void SetDepthTarget(D3D11DepthResourceParamRef DepthTargetResource) = 0;
	/// <summary>
	/// 分配渲染目标
	/// </summary>
	virtual void OMRenderTarget() = 0;

	/// <summary>
	/// 分配视口
	/// </summary>
	virtual void OMViewPort(float view_width, float  view_height) = 0;
	virtual void UpdateViewPort(ViewPortDesc* desc) = 0;
	virtual void UpdateViewPortViewMat(ViewPortDesc* desc) = 0;
	virtual void UpdateViewPortProjMat(ViewPortDesc* desc) = 0;

	virtual void CreateBlendState(D3D11BlendStateResParamRef blendStateParam) = 0;
	virtual void CreateDepthStencilState(D3D11DepthStencilStateResParamRef DepthStateParam) = 0;
	virtual void CreaRasterizerState(D3D11RasterizerStateResParamRef rasterStateParam) = 0;
	virtual void CreaTextureSampleState(D3D11TextureSampleStateParamRef rasterStateParam) = 0;

	//////////////////////////////////清理////////////////////////////////////////

	/// <summary>
	/// 清理RenderTarget
	/// </summary>
	virtual void ClearRMT(D3D11RHIRenderTargetParamRef RenderTargetResource) = 0;
	/// <summary>
	/// Clears the depth view.
	/// </summary>
	/// <param name="DepthTargetResource">The depth target resource.</param>
	virtual void ClearDepthView(D3D11DepthResourceParamRef DepthTargetResource) = 0;


	//////////////////////////////////状态分配////////////////////////////////////////
	virtual void SetPrimitiveTology(PrimitiveTopology pDrawType) = 0;


	//////////////////////////////////状态分配////////////////////////////////////////
	/// <summary>
	/// Sets the state of the rasterizer.
	/// </summary>
	/// <param name="rasterizerStateParam">The rasterizer state parameter.</param>
	virtual void SetRasterizerState(D3D11RasterizerStateResParamRef rasterizerStateParam) = 0;
	virtual void SetDepthState(D3D11DepthStencilStateResParamRef depthStateParam) = 0;
	virtual void SetBlendState(D3D11BlendStateResParamRef blendStateParam) = 0;




	//////////////////////////////////纹理采样模式分配////////////////////////////////////////
	virtual void SetTextureSample(D3D11TextureSampleStateParamRef TextureSamParam) = 0;




	//////////////////////////////////Shader分配////////////////////////////////////////
	virtual void CreateVertexShader(D3D11VertexShaderResParamRef ResTarget, FWString shaderFileName) = 0;
	virtual void CreatePixelShader(D3D11PixelShaderResParamRef ResTarget, FWString shaderFileName) = 0;
	virtual void CreateInputLayout(D3D11InputLayoutRes* outInput, D3DInputElementResParamRef ResTarget, D3D11VertexShaderResParamRef vertexShader) = 0;


	/// <summary>
	/// Omvses the shader.
	/// </summary>
	virtual void OMVSShader(D3D11VertexShaderResParamRef ResTarget) = 0;

	/// <summary>
	/// Ompses the shader.
	/// </summary>
	virtual void OMPSShader(D3D11PixelShaderResParamRef ResTarget) = 0;
	/// <summary>
/// Ompses the shader.
/// </summary>
	virtual void OMPInputLayout(D3D11InputLayoutResParamRef ResTarget) = 0;

	virtual void CreateShaderResourcesView(D3D11ShaderResourceViewResParamRef ResTarget, FWString filePath) =0;
	virtual void SetShaderResourcesView(int stIndex, int num, D3D11ShaderResourceViewResParamRef ResTarget, D3D11ShaderType bindShaderType) =0;
	virtual void CreateVertexBuffer(D3D11VertexBufferResParamRef ResTarget, void*data, UINT descSize, UINT numVertices) = 0;
	virtual void CreateIndexBuffer(D3D11IndexBufferResParamRef ResTarget, DWORD * pMemData, UINT numIndices) = 0;
	virtual void BindVertexBuffer(D3D11VertexBufferResParamRef ResTarget, int statIndex, int Num, UINT offset) = 0;
	virtual void BindIndexBuffer(D3D11IndexBufferResParamRef ResTarget, int statIndex, DXGI_FORMAT pformat) = 0;
	virtual void DrawIndexBuffer(D3D11IndexBufferResParamRef ResTarget, int startIndexPos, int startIndexVertex) = 0;

	/**
	 * 呈现
	 */
	virtual void Present() = 0;


	virtual void ApplyConstantBuffer(D3D11UniFormBufferRef ResTarget, UINT pDataWidth, void * pData, bool isReBind) =0;


protected:
	//virtual RHIUniFormBufferRef CreateConstantBuffer(D3D11UniFormBufferRef ResTarget, UINT pDataWidth) =0;
	virtual RHIUniFormBufferRef CreateUniFormBuffer(void* Content, UniFormLayout* layout) = 0;
	virtual void BindConstantBuffer(D3D11UniFormBufferRef ResTarget, UINT index, D3D11ShaderType bindShaderType) =0;
	
	virtual void InitDefaultRes() = 0;
	virtual void InitContantBuffer() = 0;
	virtual void InitShader() = 0;
	virtual void InitializeViewPort() = 0;
	virtual void InitDefaultState() = 0;



public:
	int view_width = 800;
	int view_height = 600;
	ViewPortDesc						mViewPortDesc;

	D3D11RHIRenderTargetParamRef		mMainRenderTarget;
	D3D11DepthResourceParamRef			mMainDepthRes;

	D3D11UniFormBufferRef		mCBStates;
	D3D11UniFormBufferRef		mCBFrame;
	D3D11UniFormBufferRef		mCBOnResize;
	D3D11UniFormBufferRef		mCBRarely;
	D3D11UniFormBufferRef		mCBDraw;

	D3D11VertexShaderRes*				mDefaultVertexShader;
	D3D11PixelShaderRes*				mDefaultPixelShader;
	D3D11InputLayoutRes*				mDefaultInputLayout;

	D3D11RasterizerStateRes*			mDefaultRasState;
	D3D11DepthStencilStateRes*			mDefaultDepthState;
	D3D11BlendStateRes*					mDefaultBlendState;
	D3D11TextureSampleState*			mDefaultTextureSampleState;
};





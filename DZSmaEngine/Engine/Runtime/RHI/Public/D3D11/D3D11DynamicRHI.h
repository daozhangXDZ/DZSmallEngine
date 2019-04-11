#pragma once
#include "DynamicRHI.h"
#include <wrl/client.h>
#include <d3d11.h>
#include <DirectXMath.h>
#include "EngineGlobal.h"

using namespace DirectX;

/// <summary>
/// DX渲染口
/// </summary>
/// <seealso cref="DynamicRHI" />
class D3D11DynamicRHI : public DynamicRHI
{
public:
	
	virtual void InitRender() override;
	virtual void Tick() override;
	virtual void Exit() override;

protected:	
	/// <summary>
	/// 开启DX设备和交换链
	/// </summary>
	virtual void InitRenderDevice() override;

	virtual void BeginDrawViewPort() override {};
	virtual void EndDrawViewPort() override {};	

public:
	/// <summary>
	/// 创建渲染目标
	/// </summary>
	virtual void CreateRenderTarget(D3D11RHIRenderTargetParamRef RenderTargetResource) override;
	virtual void SetRenderTarget(D3D11RHIRenderTargetParamRef RenderTargetResource) override;
	

	virtual void CreateDepthTarget(D3D11DepthResourceParamRef DepthTargetResource) override;
	virtual void SetDepthTarget(D3D11DepthResourceParamRef DepthTargetResource) override;
	/// <summary>
	/// 分配渲染目标
	/// </summary>
	virtual void OMRenderTarget() override;
	
	/// <summary>
	/// 分配视口
	/// </summary>
	virtual void OMViewPort(float view_width, float  view_height) override;
	virtual void UpdateViewPort(ViewPortDesc* desc) override;
	virtual void UpdateViewPortViewMat(ViewPortDesc* desc) override;
	virtual void UpdateViewPortProjMat(ViewPortDesc* desc) override;

	virtual void CreateBlendState(D3D11BlendStateResParamRef blendStateParam) override;
	virtual void CreateDepthStencilState(D3D11DepthStencilStateResParamRef DepthStateParam) override;
	virtual void CreaRasterizerState(D3D11RasterizerStateResParamRef rasterStateParam) override;
	virtual void CreaTextureSampleState(D3D11TextureSampleStateParamRef rasterStateParam) override;
	
	//////////////////////////////////清理////////////////////////////////////////

	/// <summary>
	/// 清理RenderTarget
	/// </summary>
	virtual void ClearRMT(D3D11RHIRenderTargetParamRef RenderTargetResource) override;	
	/// <summary>
	/// Clears the depth view.
	/// </summary>
	/// <param name="DepthTargetResource">The depth target resource.</param>
	virtual void ClearDepthView(D3D11DepthResourceParamRef DepthTargetResource) override;
	

	//////////////////////////////////状态分配////////////////////////////////////////
	virtual void SetPrimitiveTology(PrimitiveTopology pDrawType) override;
	
	
	//////////////////////////////////状态分配////////////////////////////////////////
	/// <summary>
	/// Sets the state of the rasterizer.
	/// </summary>
	/// <param name="rasterizerStateParam">The rasterizer state parameter.</param>
	virtual void SetRasterizerState(D3D11RasterizerStateResParamRef rasterizerStateParam) override;
	virtual void SetDepthState(D3D11DepthStencilStateResParamRef depthStateParam) override;
	virtual void SetBlendState(D3D11BlendStateResParamRef blendStateParam) override;




	//////////////////////////////////纹理采样模式分配////////////////////////////////////////
	virtual void SetTextureSample(D3D11TextureSampleStateParamRef TextureSamParam) override;



	
	//////////////////////////////////Shader分配////////////////////////////////////////
	virtual void CreateVertexShader(D3D11VertexShaderResParamRef ResTarget, FWString shaderFileName) override;
	virtual void CreatePixelShader(D3D11PixelShaderResParamRef ResTarget, FWString shaderFileName) override;
	virtual void CreateInputLayout(D3D11InputLayoutRes* outInput, D3DInputElementResParamRef ResTarget, D3D11VertexShaderResParamRef vertexShader) override;


	/// <summary>
	/// Omvses the shader.
	/// </summary>
	virtual void OMVSShader(D3D11VertexShaderResParamRef ResTarget) override;
	
	/// <summary>
	/// Ompses the shader.
	/// </summary>
	virtual void OMPSShader(D3D11PixelShaderResParamRef ResTarget) override;
	/// <summary>
/// Ompses the shader.
/// </summary>
	virtual void OMPInputLayout(D3D11InputLayoutResParamRef ResTarget) override;


	virtual void CreateShaderResourcesView(D3D11ShaderResourceViewResParamRef ResTarget, FWString filePath) override;
	virtual void SetShaderResourcesView(int stIndex, int num, D3D11ShaderResourceViewResParamRef ResTarget, D3D11ShaderType bindShaderType)override;
	virtual void CreateVertexBuffer(D3D11VertexBufferResParamRef ResTarget, void*data, UINT descSize, UINT numVertices)override;
	virtual void CreateIndexBuffer(D3D11IndexBufferResParamRef ResTarget, DWORD * pMemData, UINT numIndices) override;
	virtual void BindVertexBuffer(D3D11VertexBufferResParamRef ResTarget, int statIndex, int Num, UINT offset) override;
	virtual void BindIndexBuffer(D3D11IndexBufferResParamRef ResTarget, int statIndex, DXGI_FORMAT pformat) override;
	virtual void DrawIndexBuffer(D3D11IndexBufferResParamRef ResTarget, int startIndexPos, int startIndexVertex) override;
	/**
	 * 呈现
	 */
	virtual void Present() override;

	virtual void ApplyConstantBuffer(D3D11ConstanBufferResParamRef ResTarget, UINT pDataWidth, void * pData, bool isReBind) override;
protected:
	virtual void CreateConstantBuffer(D3D11ConstanBufferResParamRef ResTarget, UINT pDataWidth) override;
	virtual void BindConstantBuffer(D3D11ConstanBufferResParamRef ResTarget, UINT index, D3D11ShaderType bindShaderType) override;

	virtual void InitDefaultRes() override;
	virtual void InitContantBuffer() override;
	virtual void InitShader() override;
	virtual void InitializeViewPort() override;
	virtual void InitDefaultState() override;

private:
	Microsoft::WRL::ComPtr< ID3D11Device >				md3d11Device;
	Microsoft::WRL::ComPtr< ID3D11DeviceContext >		md3d11DeviceContext;
	Microsoft::WRL::ComPtr < IDXGISwapChain	>			mdxgiSwapChain;

	Microsoft::WRL::ComPtr< ID3D11RenderTargetView	>	md3d11RenderTargetView;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView>		mDepthStencilView;

	
};




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
/// DX��Ⱦ��
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
	/// ����DX�豸�ͽ�����
	/// </summary>
	virtual void InitRenderDevice() override;

	virtual void BeginDrawViewPort() override {};
	virtual void EndDrawViewPort() override {};	

public:
	/// <summary>
	/// ������ȾĿ��
	/// </summary>
	virtual RHIRenderTargetRef CreateRenderTarget(uint32 width, uint32 height) override;
	virtual void SetRenderTarget(RHIRenderTargetParamRef RenderTargetResource) override;
	

	virtual RHIDepthTargetRef CreateDepthTarget() override;
	virtual void SetDepthTarget(RHIDepthTargetParamRef DepthTargetResource) override;
	/// <summary>
	/// ������ȾĿ��
	/// </summary>
	virtual void OMRenderTarget(RHIRenderTargetRef RenTarRef, RHIDepthTargetRef defRef) override;
	
	/// <summary>
	/// �����ӿ�
	/// </summary>
	virtual void OMViewPort(float view_width, float  view_height) override;

	virtual RHIBlendStateRef CreateBlendState() override;
	virtual RHIDepthStencilStateRef CreateDepthStencilState() override;
	virtual RHIRasterizerStateRef CreaRasterizerState() override;
	virtual RHISampleStateRef CreaTextureSampleState() override;
	
	//////////////////////////////////����////////////////////////////////////////

	/// <summary>
	/// ����RenderTarget
	/// </summary>
	virtual void ClearRMT(RHIRenderTargetParamRef RenderTargetResource) override;
	/// <summary>
	/// Clears the depth view.
	/// </summary>
	/// <param name="DepthTargetResource">The depth target resource.</param>
	virtual void ClearDepthView(RHIDepthTargetParamRef DepthTargetResource) override;
	

	//////////////////////////////////״̬����////////////////////////////////////////
	virtual void SetPrimitiveTology(PrimitiveTopology pDrawType) override;
	
	
	//////////////////////////////////״̬����////////////////////////////////////////
	/// <summary>
	/// Sets the state of the rasterizer.
	/// </summary>
	/// <param name="rasterizerStateParam">The rasterizer state parameter.</param>
	virtual void SetRasterizerState(RHIRasterizerStateParamRef rasterizerStateParam) override;
	virtual void SetDepthState(RHIDepthStencilStateParamRef depthStateParam) override;
	virtual void SetBlendState(RHIBlendStateParamRef blendStateParam) override;




	//////////////////////////////////�������ģʽ����////////////////////////////////////////
	virtual void SetTextureSample(RHISampleStateParamRef TextureSamParam) override;



	
	//////////////////////////////////Shader����////////////////////////////////////////
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
	 * ������ɫ����Դ��ͼ
	 */
	virtual RHIShaderResourceViewRef CreateShaderResourcesView(FWString filePath) override;
	/**
	 * ������ɫ����Դ��ͼ
	 */
	virtual void SetShaderRessourcesView(int stIndex, int num, RHIShaderResourceViewParamRef ResTarget, EShaderFrequency bindShaderType)override;

	virtual RHIVertexBufferRef CreateVertexBuffer(void*data, UINT descSize, UINT numVertices)override;
	virtual RHIIndexBufferRef CreateIndexBuffer(DWORD * pMemData, UINT numIndices) override;

	virtual void BindVertexBuffer(RHIVertexBufferParamRef ResTarget, int statIndex, int Num, UINT offset) override;
	virtual void BindIndexBuffer(RHIIndexBufferParamRef ResTarget, int statIndex, DXGI_FORMAT pformat) override;

	virtual void DrawIndexBuffer(RHIIndexBufferParamRef ResTarget, int startIndexPos, int startIndexVertex) override;
	/**
	 * ����
	 */
	virtual void Present() override;

	virtual void ApplyConstantBuffer(RHIUniFormBufferRef ResTarget, void * pData, bool isReBind) override;

	/**
	 * ����������
	 */
	virtual RHIUniFormBufferRef CreateUniFormBuffer(void* Content, UniFormLayout* layout) final override;
	/**
	 * ���ö��㻺����
	 */
	virtual void SetUniFormBuffer(RHIVertexShaderRef shader, RHIUniFormBufferParamRef ResTarget, UINT BufferIndex) final override;
	virtual void SetUniFormBuffer(RHIComputerShader shader, RHIUniFormBufferParamRef ResTarget, UINT BufferIndex)  final override;
	virtual void SetUniFormBuffer(RHIPixelShaderRef shader, RHIUniFormBufferParamRef ResTarget, UINT BufferIndex)	final override;

private:
	Microsoft::WRL::ComPtr< ID3D11Device >				md3d11Device;
	Microsoft::WRL::ComPtr< ID3D11DeviceContext >		md3d11DeviceContext;
	Microsoft::WRL::ComPtr < IDXGISwapChain	>			mdxgiSwapChain;	
};




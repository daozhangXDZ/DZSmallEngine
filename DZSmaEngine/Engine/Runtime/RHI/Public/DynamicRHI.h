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
	virtual void InitRender()
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
	/// <summary>
	/// ������ȾĿ��
	/// </summary>
	virtual RHIRenderTargetRef CreateRenderTarget(uint32 width, uint32 height) = 0;
	virtual void SetRenderTarget(RHIRenderTargetParamRef RenderTargetResource) = 0;


	virtual RHIDepthTargetRef CreateDepthTarget() = 0;
	virtual void SetDepthTarget(RHIDepthTargetParamRef DepthTargetResource) = 0;
	/// <summary>
	/// ������ȾĿ��
	/// </summary>
	virtual void OMRenderTarget(RHIRenderTargetRef RenTarRef, RHIDepthTargetRef defRef) = 0;

	/// <summary>
	/// �����ӿ�
	/// </summary>
	virtual void OMViewPort(float view_width, float  view_height) = 0;

	virtual RHIBlendStateRef CreateBlendState() = 0;
	virtual RHIDepthStencilStateRef CreateDepthStencilState() = 0;
	virtual RHIRasterizerStateRef CreaRasterizerState() = 0;
	virtual RHISampleStateRef CreaTextureSampleState() = 0;

	//////////////////////////////////����////////////////////////////////////////

	/// <summary>
	/// ����RenderTarget
	/// </summary>
	virtual void ClearRMT(RHIRenderTargetParamRef RenderTargetResource) = 0;
	/// <summary>
	/// Clears the depth view.
	/// </summary>
	/// <param name="DepthTargetResource">The depth target resource.</param>
	virtual void ClearDepthView(RHIDepthTargetParamRef DepthTargetResource) = 0;


	//////////////////////////////////״̬����////////////////////////////////////////
	virtual void SetPrimitiveTology(PrimitiveTopology pDrawType) = 0;


	//////////////////////////////////״̬����////////////////////////////////////////
	/// <summary>
	/// Sets the state of the rasterizer.
	/// </summary>
	/// <param name="rasterizerStateParam">The rasterizer state parameter.</param>
	virtual void SetRasterizerState(RHIRasterizerStateParamRef rasterizerStateParam) = 0;
	virtual void SetDepthState(RHIDepthStencilStateParamRef depthStateParam) = 0;
	virtual void SetBlendState(RHIBlendStateParamRef blendStateParam) = 0;




	//////////////////////////////////�������ģʽ����////////////////////////////////////////
	virtual void SetTextureSample(RHISampleStateParamRef TextureSamParam) = 0;




	//////////////////////////////////Shader����////////////////////////////////////////
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
	 * ������ɫ����Դ��ͼ
	 */
	virtual RHIShaderResourceViewRef CreateShaderResourcesView(FWString filePath) = 0;
	/**
	 * ������ɫ����Դ��ͼ
	 */
	virtual void SetShaderRessourcesView(int stIndex, int num, RHIShaderResourceViewParamRef ResTarget, EPipeLineFlag bindShaderType) = 0;


	virtual RHIVertexBufferRef CreateVertexBuffer(void*data, UINT descSize, UINT numVertices) = 0;
	virtual RHIIndexBufferRef CreateIndexBuffer(DWORD * pMemData, UINT numIndices) = 0;

	virtual void BindVertexBuffer(RHIVertexBufferParamRef ResTarget, int statIndex, int Num, UINT offset) = 0;
	virtual void BindIndexBuffer(RHIIndexBufferParamRef ResTarget, int statIndex, DXGI_FORMAT pformat) = 0;

	virtual void DrawIndexBuffer(RHIIndexBufferParamRef ResTarget, int startIndexPos, int startIndexVertex) = 0;

	/**
	 * ����
	 */
	virtual void Present() = 0;


	virtual void ApplyConstantBuffer(RHIUniFormBufferRef ResTarget, void * Content, bool isReBind) = 0;


	//virtual RHIUniFormBufferRef CreateConstantBuffer(D3D11UniFormBufferRef ResTarget, UINT pDataWidth) =0;
	/**
	 * ����������
	 */
	virtual RHIUniFormBufferRef CreateUniFormBuffer(void* Content, UniFormLayout* layout) = 0;
	/**
	 * ���ö��㻺����
	 */
	virtual void SetUniFormBuffer(RHIVertexShaderRef shader, RHIUniFormBufferParamRef ResTarget, UINT BufferIndex) = 0;
	virtual void SetUniFormBuffer(RHIComputerShader shader, RHIUniFormBufferParamRef ResTarget, UINT BufferIndex) = 0;
	virtual void SetUniFormBuffer(RHIPixelShaderRef shader, RHIUniFormBufferParamRef ResTarget, UINT BufferIndex) = 0;

public:
	int view_width = 800;
	int view_height = 600;
	ViewPortDesc	mViewPortDesc;
};
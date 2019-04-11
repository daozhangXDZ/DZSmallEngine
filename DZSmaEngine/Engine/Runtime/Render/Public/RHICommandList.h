#pragma once
#include "CoreMinimal.h"
#include "EngineGlobal.h"
class RHICommandListBase
{

};


class RHICommandListImmediate:public RHICommandListBase
{

};

inline void RHICreateRenderTarget(D3D11RHIRenderTargetParamRef RenderTargetResource)
{
	GDynamicRHI->CreateRenderTarget(RenderTargetResource);
}

inline void RHISetRenderTarget(D3D11RHIRenderTargetParamRef RenderTargetResource)
{
	GDynamicRHI->SetRenderTarget(RenderTargetResource);
}


inline void RHICreateDepthTarget(D3D11DepthResourceParamRef DepthTargetResource)
{
	GDynamicRHI->CreateDepthTarget(DepthTargetResource);
}

inline void RHISetDepthTarget(D3D11DepthResourceParamRef DepthTargetResource)
{
	GDynamicRHI->SetDepthTarget(DepthTargetResource);
}
/// <summary>
/// 分配渲染目标
/// </summary>
inline void RHIOMRenderTarget()
{
	GDynamicRHI->OMRenderTarget();
}

/// <summary>
/// 分配视口
/// </summary>
inline void RHIOMViewPort(float view_width, float  view_height)
{
	GDynamicRHI->OMViewPort(view_width, view_height);
}

inline void RHISyncCamera(ViewPortDesc* desc)
{
	GDynamicRHI->UpdateViewPort(desc);
}

inline void RHICreateBlendState(D3D11BlendStateResParamRef blendStateParam)
{
	GDynamicRHI->CreateBlendState(blendStateParam);
}

inline void RHICreateDepthStencilState(D3D11DepthStencilStateResParamRef DepthStateParam)
{
	GDynamicRHI->CreateDepthStencilState(DepthStateParam);
}

inline void RHICreaRasterizerState(D3D11RasterizerStateResParamRef rasterStateParam)
{
	GDynamicRHI->CreaRasterizerState(rasterStateParam);
}

inline void RHICreaTextureSampleState(D3D11TextureSampleStateParamRef TextureSamplParam)
{
	GDynamicRHI->CreaTextureSampleState(TextureSamplParam);
}

//////////////////////////////////清理////////////////////////////////////////

/// <summary>
/// 清理RenderTarget
/// </summary>
inline void RHIClearRMT(D3D11RHIRenderTargetParamRef RenderTargetResource)
{
	GDynamicRHI->ClearRMT(RenderTargetResource);
}

/// <summary>
/// Clears the depth view.
/// </summary>
/// <param name="DepthTargetResource">The depth target resource.</param>
inline void RHIClearDepthView(D3D11DepthResourceParamRef DepthTargetResource)
{
	GDynamicRHI->ClearDepthView(DepthTargetResource);
}


//////////////////////////////////状态分配////////////////////////////////////////
inline void RHISetPrimitiveTology(PrimitiveTopology pDrawType)
{
	GDynamicRHI->SetPrimitiveTology(pDrawType);
}


//////////////////////////////////状态分配////////////////////////////////////////
/// <summary>
/// Sets the state of the rasterizer.
/// </summary>
/// <param name="rasterizerStateParam">The rasterizer state parameter.</param>
inline void RHISetRasterizerState(D3D11RasterizerStateResParamRef rasterizerStateParam)
{
	GDynamicRHI->SetRasterizerState(rasterizerStateParam);
}

inline void RHISetDepthState(D3D11DepthStencilStateResParamRef depthStateParam)
{
	GDynamicRHI->SetDepthState(depthStateParam);
}


inline void RHISetBlendState(D3D11BlendStateResParamRef blendStateParam)
{
	GDynamicRHI->SetBlendState(blendStateParam);
}




//////////////////////////////////纹理采样模式分配////////////////////////////////////////
inline void RHISetTextureSample(D3D11TextureSampleStateParamRef TextureSamParam)
{
	GDynamicRHI->SetTextureSample(TextureSamParam);
}




//////////////////////////////////Shader分配////////////////////////////////////////
inline void RHICreateVertexShader(D3D11VertexShaderResParamRef ResTarget, FWString shaderFileName)
{
	GDynamicRHI->CreateVertexShader(ResTarget, shaderFileName);
}

inline void RHICreatePixelShader(D3D11PixelShaderResParamRef ResTarget, FWString shaderFileName)
{
	GDynamicRHI->CreatePixelShader(ResTarget, shaderFileName);
}

inline void RHICreateInputLayout(D3D11InputLayoutRes* outInput, D3DInputElementResParamRef ResTarget, D3D11VertexShaderResParamRef vertexShader)
{
	GDynamicRHI->CreateInputLayout(outInput,ResTarget, vertexShader);
}


/// <summary>
/// Omvses the shader.
/// </summary>
inline void RHIOMVSShader(D3D11VertexShaderResParamRef ResTarget)
{
	GDynamicRHI->OMVSShader(ResTarget);
}

/// <summary>
/// Ompses the shader.
/// </summary>
inline void RHIOMPSShader(D3D11PixelShaderResParamRef ResTarget)
{
	GDynamicRHI->OMPSShader(ResTarget);
}
/// <summary>
/// Ompses the shader.
/// </summary>
inline void RHIOMPInputLayout(D3D11InputLayoutResParamRef ResTarget)
{
	GDynamicRHI->OMPInputLayout(ResTarget);
}

inline void RHICreateShaderResourcesView(D3D11ShaderResourceViewResParamRef ResTarget, FWString filePath)
{
	GDynamicRHI->CreateShaderResourcesView(ResTarget, filePath);
}

inline void RHISetShaderResourcesView(int stIndex, int num, D3D11ShaderResourceViewResParamRef ResTarget, D3D11ShaderType bindShaderType)
{
	GDynamicRHI->SetShaderResourcesView(stIndex, num, ResTarget, bindShaderType);
}

inline void RHICreateVertexBuffer(D3D11VertexBufferResParamRef ResTarget, void*data, UINT descSize, UINT numVertices)
{
	GDynamicRHI->CreateVertexBuffer(ResTarget, data,descSize,numVertices);
}

inline void RHICreateIndexBuffer(D3D11IndexBufferResParamRef ResTarget, DWORD * pMemData, UINT numIndices)
{
	GDynamicRHI->CreateIndexBuffer(ResTarget, pMemData, numIndices);
}


inline void RHIBindVertexBuffer(D3D11VertexBufferResParamRef ResTarget, int statIndex, int Num, UINT offset)
{
	GDynamicRHI->BindVertexBuffer(ResTarget, statIndex, Num, offset);
}

inline void RHIBindIndexBuffer(D3D11IndexBufferResParamRef ResTarget, int statIndex, DXGI_FORMAT pformat)
{
	GDynamicRHI->BindIndexBuffer(ResTarget, statIndex, pformat);
}

inline void RHIDrawIndexBuffer(D3D11IndexBufferResParamRef ResTarget, int startIndexPos, int startIndexVertex)
{
	GDynamicRHI->DrawIndexBuffer(ResTarget, startIndexPos, startIndexVertex);
}

inline void RHIUpdateViewProject(ViewPortDesc* desc)
{
	GDynamicRHI->UpdateViewPort(desc);
}

inline void RHIUpdateViewPortProjMat(ViewPortDesc* desc)
{
	GDynamicRHI->UpdateViewPortProjMat(desc);
}

inline void RHIUpdateViewPortViewMat(ViewPortDesc* desc)
{
	GDynamicRHI->UpdateViewPortViewMat(desc);
}


/// <summary>
/// Rhis the apply constant buffer.
/// </summary>
/// <param name="ResTarget">The resource target.</param>
/// <param name="pDataWidth">Width of the p data.</param>
/// <param name="pData">The p data.</param>
template<typename T>
inline void RHIChangeConstanBuffer(T* pRaram, bool isNeedApply)
{
	return;
}


template<>
inline void RHIChangeConstanBuffer(CBChangesEveryDrawing * pData, bool isNeedApply)
{
	GDynamicRHI->ApplyConstantBuffer(GDynamicRHI->mCBDraw, sizeof(CBChangesEveryDrawing), pData, isNeedApply);
}

template<>
inline void RHIChangeConstanBuffer(CBDrawingStates * pData, bool isNeedApply)
{
	GDynamicRHI->ApplyConstantBuffer(GDynamicRHI->mCBStates, sizeof(CBDrawingStates), pData, isNeedApply);
}
template<>
inline void RHIChangeConstanBuffer(CBChangesEveryFrame * pData, bool isNeedApply)
{
	GDynamicRHI->ApplyConstantBuffer(GDynamicRHI->mCBFrame, sizeof(CBChangesEveryFrame), pData, isNeedApply);
}
template<>
inline void RHIChangeConstanBuffer(CBChangesOnResize * pData, bool isNeedApply)
{
	GDynamicRHI->ApplyConstantBuffer(GDynamicRHI->mCBOnResize, sizeof(CBChangesOnResize), pData, isNeedApply);
}

template<>
inline void RHIChangeConstanBuffer(CBChangesRarely * pData, bool isNeedApply)
{
	GDynamicRHI->ApplyConstantBuffer(GDynamicRHI->mCBRarely, sizeof(CBChangesRarely), pData, isNeedApply);
}

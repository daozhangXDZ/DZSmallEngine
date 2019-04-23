#pragma once
#include "CoreMinimal.h"
#include "EngineGlobal.h"
#include "RHIGlobalState.h"
#include "RHIGlobalUniform.h"
class RHICommandListBase
{
protected:
	/**
	 * RHI缓冲区
	 */
	RHIGlobalUniform*					mUniformBuffer = nullptr;
	RHIGlobalState*						mRenderState = nullptr;
public:
	RHICommandListBase()
	{
		if (mUniformBuffer == nullptr)
		{
			mUniformBuffer = new RHIGlobalUniform();
			mUniformBuffer->Init();
		}
		if (mRenderState == nullptr)
		{
			mRenderState = new RHIGlobalState();
			mRenderState->Init();
		}
	}

	RHIGlobalUniform* GetGlobalUniForm()
	{
		return mUniformBuffer;
	}

	RHIGlobalState* GetGlobalRHIState()
	{
		return mRenderState;
	}

	~RHICommandListBase()
	{
		if (mRenderState)
		{
			delete mRenderState;
			mRenderState = nullptr;
		}
	}
};


class RHICommandListImmediate:public RHICommandListBase
{
public:
	RHICommandListImmediate() :RHICommandListBase()
	{

	}
};


class RHICommandList :public RHICommandListBase
{
public:
	RHICommandList() :RHICommandListBase()
	{

	}
};

/// <summary>
	/// 创建渲染目标
	/// </summary>
inline RHIRenderTargetRef RHICreateRenderTarget(RHITextureParamRef NewRenderTarget, RHITextureParamRef NewDepthStencilTarget, bool bWritableBarrier = false)
{
	
}

inline void RHISetRenderTarget(RHIRenderTargetParamRef RenderTargetResource, RHIDepthTargetParamRef DepthTargetParam)
{
	GDynamicRHI->SetRenderTarget(RenderTargetResource, DepthTargetParam);
}


/// <summary>
/// 分配渲染目标
/// </summary>
inline void RHIOMRenderTarget()
{
	GDynamicRHI->CommitRenderTargetsAndUAVs();
}

/// <summary>
/// 分配视口
/// </summary>
inline void RHIOMViewPort(float view_width, float  view_height)
{
	GDynamicRHI->OMViewPort(view_width, view_height);
}

inline RHIBlendStateRef RHICreateBlendState()
{
	return GDynamicRHI->CreateBlendState();
}

inline RHIDepthStencilStateRef RHICreateDepthStencilState()
{
	return GDynamicRHI->CreateDepthStencilState();
}

inline RHIRasterizerStateRef RHICreaRasterizerState()
{
	return GDynamicRHI->CreaRasterizerState();
}

inline RHISampleStateRef RHICreaTextureSampleState()
{
	return GDynamicRHI->CreaTextureSampleState();
}
//////////////////////////////////清理////////////////////////////////////////

/// <summary>
/// 清理RenderTarget
/// </summary>
inline void RHIClearRMT()
{
	GDynamicRHI->ClearRMT();
}
/// <summary>
/// Clears the depth view.
/// </summary>
/// <param name="DepthTargetResource">The depth target resource.</param>
inline void RHIClearDepthView()
{
	GDynamicRHI->ClearDepthView();
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
inline void RHISetRasterizerState(RHIRasterizerStateParamRef rasterizerStateParam)
{
	GDynamicRHI->SetRasterizerState(rasterizerStateParam);
}

inline void RHISetDepthState(RHIDepthStencilStateParamRef depthStateParam)
{
	GDynamicRHI->SetDepthState(depthStateParam);
}

inline void RHISetBlendState(RHIBlendStateParamRef blendStateParam)
{
	GDynamicRHI->SetBlendState(blendStateParam);
}




//////////////////////////////////纹理采样模式分配////////////////////////////////////////
inline void RHISetTextureSample(RHISampleStateParamRef TextureSamParam)
{
	GDynamicRHI->SetTextureSample(TextureSamParam);
}




//////////////////////////////////Shader分配////////////////////////////////////////
inline RHIVertexShaderRef RHICreateVertexShader(FWString shaderFileName)
{
	return GDynamicRHI->CreateVertexShader(shaderFileName);
}

inline RHIPixelShaderRef RHICreatePixelShader(FWString shaderFileName)
{
	return GDynamicRHI->CreatePixelShader(shaderFileName);
}

inline RHIVertexLayoutRef RHICreateInputLayout(RHIVertexInputElementParamRef ResTarget, RHIVertexShaderParamRef vertexShader)
{
	return GDynamicRHI->CreateInputLayout(ResTarget,vertexShader);
}


/// <summary>
/// Omvses the shader.
/// </summary>
inline void RHIOMVSShader(RHIVertexShaderParamRef ResTarget)
{
	GDynamicRHI->OMVSShader(ResTarget);
}

/// <summary>
/// Ompses the shader.
/// </summary>
inline void RHIOMPSShader(RHIPixelShaderParamRef ResTarget)
{
	GDynamicRHI->OMPSShader(ResTarget);
}
/// <summary>
/// Ompses the shader.
/// </summary>
inline void RHIOMPInputLayout(RHIVertexLayoutRef ResTarget)
{
	GDynamicRHI->OMPInputLayout(ResTarget);
}


/**
 * 创建着色器资源视图
 */
inline RHIShaderResourceViewRef RHICreateShaderResourcesView(FWString mainTextureFilePath, ETextureSrcFormat srcFormat)
{
	return GDynamicRHI->CreateShaderResourcesView(mainTextureFilePath, srcFormat);
}
/**
 * 设置着色器资源视图
 */
inline void RHISetShaderRessourcesView(int stIndex, int num, RHIShaderResourceViewParamRef ResTarget, EShaderFrequency bindShaderType)
{
	GDynamicRHI->SetShaderRessourcesView(stIndex, num, ResTarget, bindShaderType);
}


inline RHIVertexBufferRef RHICreateVertexBuffer(void* data, UINT descSize, UINT numVertices)
{
	return GDynamicRHI->CreateVertexBuffer(data, descSize, numVertices);
}

inline RHIIndexBufferRef RHICreateIndexBuffer(DWORD * pMemData, UINT numIndices)
{
	return GDynamicRHI->CreateIndexBuffer(pMemData, numIndices);
}

inline void RHIBindVertexBuffer(RHIVertexBufferParamRef ResTarget, int statIndex, int Num, UINT offset)
{
	GDynamicRHI->BindVertexBuffer(ResTarget, statIndex, Num, offset);
}

inline void RHIBindIndexBuffer(RHIIndexBufferParamRef ResTarget, int statIndex, DXGI_FORMAT pformat)
{
	GDynamicRHI->BindIndexBuffer(ResTarget, statIndex, pformat);
}

inline void RHIDrawIndexBuffer(RHIIndexBufferParamRef ResTarget, int startIndexPos, int startIndexVertex)
{
	GDynamicRHI->DrawIndexBuffer(ResTarget, startIndexPos, startIndexVertex);
}

/**
 * 呈现
 */
inline void RHIPresent()
{
	GDynamicRHI->Present();
}


inline void RHIApplyConstantBuffer(RHIUniFormBufferRef ResTarget, void * Content, bool isReBind)
{
	GDynamicRHI->ApplyConstantBuffer(ResTarget, Content, isReBind);
}


//inline RHIUniFormBufferRef CreateConstantBuffer(D3D11UniFormBufferRef ResTarget, UINT pDataWidth) =0;
/**
 * 创建缓冲区
 */
inline RHIUniFormBufferRef RHICreateUniFormBuffer(void* Content, UniFormLayout* layout)
{
	return GDynamicRHI->CreateUniFormBuffer(Content, layout);
}

/**
 * 设置顶点缓冲区
 */
template<typename T>
inline void RHISetUniFormBuffer(T shader, RHIUniFormBufferParamRef ResTarget, UINT BufferIndex)
{
	GDynamicRHI->SetUniFormBuffer(shader, ResTarget,BufferIndex);
}


/// <summary>
/// Rhis the apply constant buffer.
/// </summary>
/// <param name="ResTarget">The resource target.</param>
/// <param name="pDataWidth">Width of the p data.</param>
/// <param name="pData">The p data.</param>
template<typename T>
inline void RHIChangeConstanBuffer(RHIUniFormBufferRef UniForm,T* pRaram, bool isNeedApply)
{
	GDynamicRHI->ApplyConstantBuffer(UniForm, pRaram, isNeedApply);
}


inline RHIVertexInputElementRef RHICreateRHIInputElement(const D3D11_INPUT_ELEMENT_DESC* pDesc, uint32 num)
{
	RHIVertexInputElementRef elem = new RHIVertexInputElement();
	elem->elementsDesc = const_cast<D3D11_INPUT_ELEMENT_DESC *>( pDesc);
	elem->elementsNumber = num;
	return elem;
}

//
//template<>
//inline void RHIChangeConstanBuffer(RHIUniFormBufferRef UniForm, CBChangesEveryDrawing * pData, bool isNeedApply)
//{
//	GDynamicRHI->ApplyConstantBuffer(UniForm, pData, isNeedApply);
//}
//
//template<>
//inline void RHIChangeConstanBuffer(RHIUniFormBufferRef UniForm, CBDrawingStates * pData, bool isNeedApply)
//{
//	GDynamicRHI->ApplyConstantBuffer(UniForm, pData, isNeedApply);
//}
//template<>
//inline void RHIChangeConstanBuffer(RHIUniFormBufferRef UniForm, CBChangesEveryFrame * pData, bool isNeedApply)
//{
//	GDynamicRHI->ApplyConstantBuffer(UniForm, pData, isNeedApply);
//}
//template<>
//inline void RHIChangeConstanBuffer(RHIUniFormBufferRef UniForm, CBChangesOnResize * pData, bool isNeedApply)
//{
//	GDynamicRHI->ApplyConstantBuffer(UniForm, pData, isNeedApply);
//}
//
//template<>
//inline void RHIChangeConstanBuffer(RHIUniFormBufferRef UniForm, CBChangesRarely * pData, bool isNeedApply)
//{
//	GDynamicRHI->ApplyConstantBuffer(UniForm, pData, isNeedApply);
//}

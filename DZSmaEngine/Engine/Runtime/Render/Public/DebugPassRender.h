#pragma once
#include "RHISources.h"
#include "VertexElementDesc.h"
#include "RHICommandList.h"
class DebugShowUI
{
public:
	RHIVertexBufferRef					mVertexBuffer = nullptr;
	RHIIndexBufferRef					mIndexBuffer = nullptr;
	RHIVertexShaderRef					mVertexShader = nullptr;
	RHIPixelShaderRef					mPixelShader = nullptr;
	RHIVertexInputElementRef			mInputElement = nullptr;
	RHIVertexLayoutRef					mInputLayout = nullptr;




	

	std::vector<VertexPosNormalTangentTex> mVertexData;
	std::vector<DWORD> mIndexData;
};


class DebugShowPolicy
{
public:
	DebugShowUI* DepthDebugUIS;
	DebugShowUI* BasePassResult;

	RHIBlendStateParamRef			BlendState;
	RHIRasterizerStateParamRef		RasterizerState;
	RHIDepthStencilStateParamRef	DepthStencilState;
	EPixelFormat					RenderTargetFormat;
	PrimitiveTopology				mPrimitiveToPology;
public:
	void Init();
	void Draw(RHICommandList* RHICmdList);
};
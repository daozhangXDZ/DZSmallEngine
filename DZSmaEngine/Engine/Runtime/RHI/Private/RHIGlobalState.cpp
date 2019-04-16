#include "RHIGlobalState.h"
#include "RHICommandList.h"

void RHIGlobalState::Init()
{
	
	//创建渲染状态 也可以放到 Render中  Simple就简单直接初始化一次
	mDefaultRasState = RHICreaRasterizerState();
	mDefaultDepthState = RHICreateDepthStencilState();
	mDefaultBlendState = RHICreateBlendState();
	mDefaultTextureSampleState = RHICreaTextureSampleState();
}

void RHIGlobalState::Clear()
{
}

RHIRasterizerStateRef RHIGlobalState::GetRHIDefaultRasState()
{
	return mDefaultRasState;
}
RHIDepthStencilStateRef RHIGlobalState::GetDefaultDepthState()
{
	return mDefaultDepthState;
}
RHIBlendStateRef RHIGlobalState::GetDefaultBlendState()
{
	return mDefaultBlendState;
}
RHISampleStateRef RHIGlobalState::GetDefaultTextureSampleState()
{
	return mDefaultTextureSampleState;
}
#include "RHIGlobalState.h"
#include "RHICommandList.h"

void RHIGlobalState::Init()
{
	
	//������Ⱦ״̬ Ҳ���Էŵ� Render��  Simple�ͼ�ֱ�ӳ�ʼ��һ��
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
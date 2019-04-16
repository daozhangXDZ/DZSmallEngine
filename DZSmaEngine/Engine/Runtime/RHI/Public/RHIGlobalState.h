#pragma once
#include "RHIState.h"

class RHIGlobalState
{
	RHIRasterizerStateRef				mDefaultRasState;
	RHIDepthStencilStateRef				mDefaultDepthState;
	RHIBlendStateRef					mDefaultBlendState;
	RHISampleStateRef					mDefaultTextureSampleState;

public:
	RHIRasterizerStateRef GetRHIDefaultRasState();
	RHIDepthStencilStateRef GetDefaultDepthState();
	RHIBlendStateRef GetDefaultBlendState();
	RHISampleStateRef GetDefaultTextureSampleState();
public:
	void Init();
	void Clear();
};
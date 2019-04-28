#include "RHICommandList.h"

void RHICommandListImmediate::CachePreRenderTarget()
{
	RHITexture2DParamRef vCacheT = RHIGetRenderTarget(800, 600, EPixelFormat::PF_R8G8B8A8_UINT);
	vCahce_RTargetViewParam = new RHIRenderTarget(vCacheT);
	vCahce_DTargetViewParam = new RHIDepthTarget(vCacheT);
}

void  RHICommandListImmediate::ResetCachePreRenderTarget()
{
	RHISetRenderTarget(vCahce_RTargetViewParam, vCahce_DTargetViewParam);
	RHIOMRenderTarget();
	vCahce_RTargetViewParam->Release();
	vCahce_DTargetViewParam->Release();
}
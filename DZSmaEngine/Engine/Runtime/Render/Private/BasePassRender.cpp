#include "SimpleShadingRender.h"

void SimpleShadingRender::RenderBasePass(RHICommandListImmediate* RHICMDList, std::vector<PrimitiveSceneProxy*>* RenderProxyList)
{
	static float dtZ;
	static float speed = 0.0001f;
	RHIOMViewPort(800.0f, 600.0f);
	RHIClearRMT();
	RHIClearDepthView();
	RHISetRasterizerState(RHICMDList->GetGlobalRHIState()->GetRHIDefaultRasState());
	RHISetDepthState(RHICMDList->GetGlobalRHIState()->GetDefaultDepthState());
	RHISetBlendState(RHICMDList->GetGlobalRHIState()->GetDefaultBlendState());
	RHISetTextureSample(RHICMDList->GetGlobalRHIState()->GetDefaultTextureSampleState());
	{
		vRarelyCSB.dirLight[0].Ambient = XMFLOAT4(0.5f + dtZ, 0.5f + dtZ, 0.5f + dtZ, 1.0f);
		RHIApplyConstantBuffer(RHICMDList->GetGlobalUniForm()->GetRHIRarelyBuffer(), &vRarelyCSB, true);
		dtZ += speed;
		if (dtZ > 0.5f || dtZ < -0.5f)
		{
			speed = -1 * speed;
		}
	}

	for (int i = 0; i < RenderProxyList->size(); i++)
	{
		PrimitiveSceneProxy* vItemRender = (*RenderProxyList)[i];
		vItemRender->Draw(RHICMDList);
	}
	RHIPresent();
}
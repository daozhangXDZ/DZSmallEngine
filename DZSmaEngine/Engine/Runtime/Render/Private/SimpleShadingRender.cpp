#include "SimpleShadingRender.h"
#include "EngineGlobal.h"
#include "D3D11/D3D11RHIResources.h"
#include "RHICommandList.h"

void SimpleShadingRender::Render(std::vector<PrimitiveSceneProxy*>* RenderProxyList)
{
	RenderBasePass(RenderProxyList);
}

void SimpleShadingRender::UpdateViewProject(ViewPortDesc * desc,bool isUpdateProj)
{
	if (isUpdateProj)
	{
		RHIUpdateViewPortProjMat(desc);

	}
	RHIUpdateViewPortViewMat(desc);
}

void SimpleShadingRender::RenderBasePass(std::vector<PrimitiveSceneProxy*>* RenderProxyList)
{
	//GDynamicRHI->SetRenderTarget(GDynamicRHI->mMainRenderTarget);
	//GDynamicRHI->SetDepthTarget(GDynamicRHI->mMainDepthRes);
	//GDynamicRHI->OMRenderTarget();

	GDynamicRHI->ClearRMT(GDynamicRHI->mMainRenderTarget);
	GDynamicRHI->ClearDepthView(GDynamicRHI->mMainDepthRes);
	GDynamicRHI->OMPInputLayout(GDynamicRHI->mDefaultInputLayout);
	GDynamicRHI->SetPrimitiveTology(PrimitiveTopology::TRIANGLELIST);
	GDynamicRHI->SetRasterizerState(GDynamicRHI->mDefaultRasState);
	GDynamicRHI->SetDepthState(GDynamicRHI->mDefaultDepthState);
	GDynamicRHI->SetBlendState(GDynamicRHI->mDefaultBlendState);
	GDynamicRHI->SetTextureSample(GDynamicRHI->mDefaultTextureSampleState);
	GDynamicRHI->OMVSShader(GDynamicRHI->mDefaultVertexShader);
	GDynamicRHI->OMPSShader(GDynamicRHI->mDefaultPixelShader);

	for (int i=0; i<RenderProxyList->size(); i++)
	{
		PrimitiveSceneProxy* vItemRender = (*RenderProxyList)[i];
		vItemRender->Draw();
	}
	GDynamicRHI->Present();
}
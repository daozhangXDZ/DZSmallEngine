#include "SimpleShadingRender.h"
#include "BasePassRender.h"
#include "PipelineStateCache.h"
#include "ShaderUtils.h"
#include "Material/MaterialUtils.h"

void BasePaseDrawPolicy::Init()
{
	gr.BlendState = RHICreateBlendState();
	gr.DepthStencilState = RHICreateDepthStencilState();
	gr.RasterizerState = RHICreaRasterizerState();
	gr.mPrimitiveToPology = PrimitiveTopology::TRIANGLELIST;
	gr.BoundShaderState.mVertexShader = ShaderUtils::GetShaderResource(L"Basic_BasePass_VS.cso")->getVertexShader();
	gr.BoundShaderState.mPixelShader = ShaderUtils::GetShaderResource(L"Basic_BasePass_PS.cso")->getPixelShader();
	RHIVertexInputElementRef Element = RHICreateRHIInputElement(VertexPosNormalTangentTex::inputLayout
		, ARRAYSIZE(VertexPosNormalTangentTex::inputLayout));
	gr.BoundShaderState.mVertexLayout = RHICreateInputLayout(Element, gr.BoundShaderState.mVertexShader);
}


void BasePaseDrawPolicy::SetupShaderState(RHICommandListImmediate * RHICMDList)
{
	MeshDrawPolicy::SetupShaderState(RHICMDList);

	SetGraphicsPipelineState(RHICMDList, gr);
}


void BasePaseDrawPolicy::PreDraw(RHICommandListImmediate * RHICMDList, PrimitiveSceneInfo * component)
{
	MeshDrawPolicy::PreDraw(RHICMDList, component);
	if (component->materia->mMainTexture != nullptr)
	{
		RHISetShaderRessourcesView(0, 1, component->materia->mMainTexture, EShaderFrequency::SF_Pixel);
	}
	if (component->materia->mNormalTexture != nullptr)
	{
		RHISetShaderRessourcesView(1, 1, component->materia->mNormalTexture, EShaderFrequency::SF_Pixel);
	}

}



void SimpleShadingRender::RenderBasePass(RHICommandListImmediate* RHICMDList, ISceneRenderInterface* RenderScene)
{
	if (mBasePassTexture == nullptr)
	{
		mBasePassTexture = RHICreateTexture2D(800, 600, PF_R32G32B32A32_UINT, 1, 1,
			ETextureCreateFlags::TexCreate_RenderTargetable
			| ETextureCreateFlags::TexCreate_DepthStencilTargetable
			| TexCreate_ShaderResource
			| TexCreate_GenerateMipCapable
			| TexCreate_Shared);
		BasePass_RTargetViewParam = new RHIRenderTarget(mBasePassTexture);
		BasePass_DTargetViewParam = new RHIDepthTarget(mBasePassTexture);
	}

	RHICMDList->CachePreRenderTarget();

	RHISetRenderTarget(BasePass_RTargetViewParam, nullptr);
	RHIOMRenderTarget();
	RHIClearRMT();
	RHIClearDepthView();
	mBasePaseDrawPolicy.SetupShaderState(RHICMDList);
	for (int i = 0; i < RenderScene->GetDepthSceneInfoList().size(); i++)
	{
		mBasePaseDrawPolicy.PreDraw(RHICMDList, RenderScene->GetBaseSceneInfoList()[i]);
		mBasePaseDrawPolicy.DrawMesh(RHICMDList, RenderScene->GetBaseSceneInfoList()[i]);
	}	

	RHICMDList->ResetCachePreRenderTarget();
}

#include "SimpleShadingRender.h"
#include "LightPassRender.h"
#include "PipelineStateCache.h"
#include "ShaderUtils.h"
#include "Material/MaterialUtils.h"

void LightPaseDrawPolicy::Init()
{
	gr.BlendState = RHICreateBlendState();
	gr.DepthStencilState = RHICreateDepthStencilState();
	gr.RasterizerState = RHICreaRasterizerState();
	gr.mPrimitiveToPology = PrimitiveTopology::TRIANGLELIST;
	gr.BoundShaderState.mVertexShader = ShaderUtils::GetShaderResource(L"Basic_Light_VS.cso")->getVertexShader();
	gr.BoundShaderState.mPixelShader = ShaderUtils::GetShaderResource(L"Basic_Light_PS.cso")->getPixelShader();
	RHIVertexInputElementRef Element = RHICreateRHIInputElement(VertexPosNormalTangentTex::inputLayout
		, ARRAYSIZE(VertexPosNormalTangentTex::inputLayout));
	gr.BoundShaderState.mVertexLayout = RHICreateInputLayout(Element, gr.BoundShaderState.mVertexShader);
}


void LightPaseDrawPolicy::SetupShaderState(RHICommandListImmediate * RHICMDList)
{
	MeshDrawPolicy::SetupShaderState(RHICMDList);

	SetGraphicsPipelineState(RHICMDList, gr);
}


void LightPaseDrawPolicy::PreDraw(RHICommandListImmediate * RHICMDList, PrimitiveSceneInfo * component)
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


void SimpleShadingRender::RenderLightPass(RHICommandListImmediate * RHICMDList, ISceneRenderInterface * RenderScene)
{
	RHIClearRMT();
	RHIClearDepthView();
	if (mBasePassTexture != nullptr && mBasePassTexture->GetNativeShaderResourceView() != nullptr)
	{
		RHISetShaderRessourcesView(3, 1, mBasePassTexture->GetNativeShaderResourceView(), EShaderFrequency::SF_Pixel);
	}
	if (mDepthTexture != nullptr && mDepthTexture->GetNativeShaderResourceView() != nullptr)
	{
		RHISetShaderRessourcesView(4, 1, mDepthTexture->GetNativeShaderResourceView(), EShaderFrequency::SF_Vertex);
		RHISetShaderRessourcesView(4, 1, mDepthTexture->GetNativeShaderResourceView(), EShaderFrequency::SF_Pixel);
	}
	mLightPassDrawPolicy.SetupShaderState(RHICMDList);
	for (int i = 0; i < RenderScene->GetDepthSceneInfoList().size(); i++)
	{
		mLightPassDrawPolicy.PreDraw(RHICMDList, RenderScene->GetBaseSceneInfoList()[i]);
		
		mLightPassDrawPolicy.DrawMesh(RHICMDList, RenderScene->GetBaseSceneInfoList()[i]);
	}
}

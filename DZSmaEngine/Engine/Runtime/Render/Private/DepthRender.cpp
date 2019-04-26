#include "SimpleShadingRender.h"
#include "DepthRender.h"
#include "PipelineStateCache.h"
#include "ShaderUtils.h"

void DepthRenderPolicy::Init()
{
	gr.BlendState = RHICreateBlendState();
	gr.DepthStencilState = RHICreateDepthStencilState();
	gr.RasterizerState = RHICreaRasterizerState();
	gr.mPrimitiveToPology = PrimitiveTopology::TRIANGLELIST;
	gr.BoundShaderState.mVertexShader = ShaderUtils::GetShaderResource(L"Basic_Depth_VS.cso")->getVertexShader();
	gr.BoundShaderState.mPixelShader = ShaderUtils::GetShaderResource(L"Basic_Depth_PS.cso")->getPixelShader();
	RHIVertexInputElementRef Element = RHICreateRHIInputElement(VertexPosNormalTangentTex::inputLayout
		, ARRAYSIZE(VertexPosNormalTangentTex::inputLayout));
	gr.BoundShaderState.mVertexLayout = RHICreateInputLayout(Element, gr.BoundShaderState.mVertexShader);
}


void DepthRenderPolicy::SetupShaderState(RHICommandListImmediate * RHICMDList)
{
	MeshDrawPolicy::SetupShaderState(RHICMDList);
	SetGraphicsPipelineState(RHICMDList, gr);
}

void DepthRenderPolicy::PreDraw(RHICommandListImmediate * RHICMDList, PrimitiveSceneInfo * component)
{
	MeshDrawPolicy::PreDraw(RHICMDList, component);
}


void SimpleShadingRender::RenderDepth(RHICommandListImmediate* RHICMDList, ISceneRenderInterface* RenderScene)
{
	if (mDepthTexture == nullptr)
	{
		mDepthTexture = RHICreateTexture2D(800, 600, PF_R32G32B32A32_UINT, 1, 1,
			ETextureCreateFlags::TexCreate_RenderTargetable |TexCreate_ShaderResource|TexCreate_Shared);
		DepthRenderTargetViewParam = new RHIRenderTarget(mDepthTexture);
		
	}
	RHIClearRMT();
	RHIClearDepthView();
	/*RHISetRenderTarget(DepthRenderTargetViewParam, nullptr);
	RHIOMRenderTarget();
	RHIClearRMT();
	RHIClearDepthView();*/
	mDepthDrawPolicy.SetupShaderState(RHICMDList);
	for (int i=0; i< RenderScene->GetDepthSceneInfoList().size(); i++)
	{
		mDepthDrawPolicy.PreDraw(RHICMDList,RenderScene->GetDepthSceneInfoList()[i]);
		mDepthDrawPolicy.DrawMesh(RHICMDList, RenderScene->GetDepthSceneInfoList()[i]);
	}
}



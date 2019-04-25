#include "SimpleShadingRender.h"
#include "DepthRender.h"
#include "PipelineStateCache.h"
#include "ShaderUtils.h"

void DepthRenderPolicy::DrawMesh(StaticMesh* mesh)
{

}

bool FDepthDrawingPolicyFactory::DrawMesh(RHICommandListImmediate* RHICmdList, StaticMesh* mesh, PrimitiveSceneProxy* PrimitiveSceneProxy)
{
	return true;
}





void SimpleShadingRender::RenderDepth(RHICommandListImmediate* RHICMDList, std::vector<PrimitiveSceneProxy *>* RenderProxyList)
{
	//TODO : 加入深度目标

	RHIOMViewPort(800.0f, 600.0f);
	RHIClearRMT();
	RHIClearDepthView();
	RHISetPrimitiveTology(PrimitiveTopology::TRIANGLELIST);
	RHIGraphicsPipelineStateInitializer gr;
	gr.BlendState = RHICreateBlendState();
	gr.DepthStencilState = RHICreateDepthStencilState();
	gr.RasterizerState = RHICreaRasterizerState();
	gr.BoundShaderState.mVertexShader = ShaderUtils::GetShaderResource(L"Basic_Depth_VS.cso")->getVertexShader();
	gr.BoundShaderState.mPixelShader = ShaderUtils::GetShaderResource(L"Basic_Depth_PS.cso")->getPixelShader();
	RHIVertexInputElementRef Element = RHICreateRHIInputElement(VertexPosNormalTangentTex::inputLayout
		, ARRAYSIZE(VertexPosNormalTangentTex::inputLayout));
	gr.BoundShaderState.mVertexLayout = RHICreateInputLayout(Element, gr.BoundShaderState.mVertexShader);
	SetGraphicsPipelineState(RHICMDList, gr);
	/*for (int i = 0; i < RenderProxyList->size(); i++)
	{
		PrimitiveSceneProxy* vItemRender = (*RenderProxyList)[i];
		FDepthDrawingPolicyFactory::DrawMesh(RHICMDList, nullptr, vItemRender);
	}*/
}
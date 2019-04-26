#include "SimpleShadingRender.h"
#include "DebugPassRender.h"
#include "Geometry.h"

void DebugShowPolicy::Init()
{
	//1-监视深度Pass的结果
	{
		Geometry::MeshData<VertexPosNormalTangentTex, DWORD> meshdatt;
		meshdatt = Geometry::Create2DShow<VertexPosNormalTangentTex, DWORD>(-1.0f,1.0f,0.5f,0.5f);

		DepthDebugUIS = new DebugShowUI();
		
		DepthDebugUIS->mVertexBuffer = RHICreateVertexBuffer(meshdatt.vertexVec.data(),
			sizeof(VertexPosNormalTangentTex),
			(UINT)meshdatt.vertexVec.size()
		);
		DepthDebugUIS->mIndexBuffer = RHICreateIndexBuffer(meshdatt.indexVec.data(), (UINT)meshdatt.indexVec.size());

		DepthDebugUIS->mVertexShader = ShaderUtils::GetShaderResource(L"Basic_2D_VS.cso")->getVertexShader();
		DepthDebugUIS->mPixelShader = ShaderUtils::GetShaderResource(L"Basic_2D_PS.cso")->getPixelShader();
		RHIVertexInputElementRef Element = RHICreateRHIInputElement(VertexPosNormalTangentTex::inputLayout
			, ARRAYSIZE(VertexPosNormalTangentTex::inputLayout));
		DepthDebugUIS->mInputLayout = RHICreateInputLayout(Element, DepthDebugUIS->mVertexShader);
	}

	BlendState = RHICreateBlendState();
	RasterizerState = RHICreaRasterizerState();
	DepthStencilState = RHICreateDepthStencilState();
	mPrimitiveToPology = PrimitiveTopology::TRIANGLELIST;
}

void SimpleShadingRender::RenderDebug(RHICommandListImmediate* RHICMDList)
{
	
	//RHISetRenderTarget(RenderTargetViewParam, nullptr);
	//RHIClearRMT();
	//RHIClearDepthView();

	RHISetPrimitiveTology(mDebugPassPolicy.mPrimitiveToPology);
	RHISetRasterizerState(mDebugPassPolicy.RasterizerState);
	RHISetDepthState(mDebugPassPolicy.DepthStencilState);
	RHISetBlendState(mDebugPassPolicy.BlendState);
	{
		RHIOMPInputLayout(mDebugPassPolicy.DepthDebugUIS->mInputLayout);
		RHIOMVSShader(mDebugPassPolicy.DepthDebugUIS->mVertexShader);
		RHIOMPSShader(mDebugPassPolicy.DepthDebugUIS->mPixelShader);
		if (mDepthTexture!= nullptr)
		{
			RHISetShaderRessourcesView(0, 1, mDepthTexture->GetNativeShaderResourceView(), EShaderFrequency::SF_Pixel);
		}
		RHIBindIndexBuffer(mDebugPassPolicy.DepthDebugUIS->mIndexBuffer, 0, DXGI_FORMAT::DXGI_FORMAT_R32_UINT);
		UINT offset = 0;
		RHIBindVertexBuffer(mDebugPassPolicy.DepthDebugUIS->mVertexBuffer, 0, 1, offset);
		RHIDrawIndexBuffer(mDebugPassPolicy.DepthDebugUIS->mIndexBuffer, 0, 0);
	}
}
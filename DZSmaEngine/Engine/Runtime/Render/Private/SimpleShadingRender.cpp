#include "SimpleShadingRender.h"
#include "EngineGlobal.h"
#include "D3D11/D3D11RHIResources.h"
#include "RHICommandList.h"
#include "RHIUtil.h"
#include "ShaderUtils.h"

void SimpleShadingRender::UpdateViewPort(ViewPortDesc* desc, bool isUpdateProj)
{
	if (isUpdateProj)
	{
		UpdateViewPortProjMat(desc);
	}
	vFrameCSB.eyePos = XMLoadFloat3(&desc->eyepos);
	UpdateViewPortViewMat(desc);
}

void SimpleShadingRender::UpdateViewPortViewMat(ViewPortDesc* desc)
{
	vFrameCSB.view = XMMatrixTranspose(desc->viewMat);
	RHIApplyConstantBuffer(mCBFrame,	&vFrameCSB, true);
}

void SimpleShadingRender::UpdateViewPortProjMat(ViewPortDesc* desc)
{
	vResizeCSB.proj = XMMatrixTranspose(desc->ProjMat);
	RHIApplyConstantBuffer(mCBOnResize,  &vResizeCSB, true);
}


void SimpleShadingRender::InitRes()
{
	

#ifdef _DEBUG //Debug Mode
#ifdef _WIN64 //x64
	std::wstring  shaderfolder = L"..\\x64\\Debug\\Shaders\\";
#else  //x86 (Win32)
	std::wstring  shaderfolder = L"..\\Debug\\Shaders\\";
#endif
#else //Release Mode
#ifdef _WIN64 //x64
	std::wstring  shaderfolder = L"..\\x64\\Release\\Shaders\\";
#else  //x86 (Win32)
	std::wstring  shaderfolder = L"..\\Release\\Shaders\\";
#endif
#endif
	mDefaultVertexShader = RHICreateVertexShader(shaderfolder + L"Default_VS.cso");
	mDefaultPixelShader = RHICreatePixelShader(shaderfolder + L"Default_PS.cso");

	mDefaultInputElement = RHICreateRHIInputElement(VertexPosNormalTex::inputLayout
					,ARRAYSIZE(VertexPosNormalTex::inputLayout));

	mDefualtInputLayout = RHICreateInputLayout(mDefaultInputElement,mDefaultVertexShader);

	//创建基础缓冲区


	mCBDraw = RHICreateUniFormBuffer(nullptr, RHIUtil::CreateLayout(new CBChangesEveryDrawing));
	RHISetUniFormBuffer(mDefaultVertexShader, mCBDraw, 0);
	RHISetUniFormBuffer(mDefaultPixelShader, mCBDraw, 0);

	mCBStates = RHICreateUniFormBuffer(nullptr, RHIUtil::CreateLayout(new CBDrawingStates));
	RHISetUniFormBuffer(mDefaultVertexShader, mCBStates, 1);
	RHISetUniFormBuffer(mDefaultPixelShader, mCBStates, 1);

	//vFrameCSB = new CBChangesEveryFrame();
	mCBFrame = RHICreateUniFormBuffer(nullptr, RHIUtil::CreateLayout(new CBChangesEveryFrame));
	RHISetUniFormBuffer(mDefaultVertexShader, mCBFrame, 2);
	RHISetUniFormBuffer(mDefaultPixelShader, mCBFrame, 2);

	//vResizeCSB = new CBChangesOnResize();
	mCBOnResize = RHICreateUniFormBuffer(nullptr, RHIUtil::CreateLayout(new CBChangesOnResize));
	RHISetUniFormBuffer(mDefaultVertexShader, mCBOnResize, 3);

	mCBRarely = RHICreateUniFormBuffer(nullptr, RHIUtil::CreateLayout(new CBChangesRarely()));
	RHISetUniFormBuffer(mDefaultVertexShader, mCBRarely, 4);
	RHISetUniFormBuffer(mDefaultPixelShader, mCBRarely, 4);

	//初始化灯光相关渲染资源
	{
		vRarelyCSB.reflection = XMMatrixTranspose(XMMatrixReflect(XMVectorSet(0.0f, 0.0f, -1.0f, 10.0f)));
		// 环境光
		vRarelyCSB.dirLight[0].Ambient = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
		vRarelyCSB.dirLight[0].Diffuse = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
		vRarelyCSB.dirLight[0].Specular = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
		vRarelyCSB.dirLight[0].Direction = XMFLOAT3(0.0f, -1.0f, 0.0f);
		// 灯光
		vRarelyCSB.pointLight[0].Position = XMFLOAT3(0.0f, 15.0f, 0.0f);
		vRarelyCSB.pointLight[0].Ambient = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
		vRarelyCSB.pointLight[0].Diffuse = XMFLOAT4(0.6f, 0.6f, 0.6f, 1.0f);
		vRarelyCSB.pointLight[0].Specular = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
		vRarelyCSB.pointLight[0].Att = XMFLOAT3(0.0f, 0.1f, 0.0f);
		vRarelyCSB.pointLight[0].Range = 25.0f;
		RHIApplyConstantBuffer(mCBRarely, &vRarelyCSB, true);
	}


	mDefaultRenderTarget = RHICreateRenderTarget(800, 600);
	mDefaultDepthRes = RHICreateDepthTarget();
	RHISetRenderTarget(mDefaultRenderTarget);
	RHISetDepthTarget(mDefaultDepthRes);

	RHIOMRenderTarget(mDefaultRenderTarget, mDefaultDepthRes);

	//创建渲染状态 也可以放到 Render中  Simple就简单直接初始化一次
	mDefaultRasState = RHICreaRasterizerState();
	mDefaultDepthState = RHICreateDepthStencilState();
	mDefaultBlendState = RHICreateBlendState();
	mDefaultTextureSampleState = RHICreaTextureSampleState();
	RHIOMViewPort(800.0f, 600.0f);
}



void SimpleShadingRender::Render(std::vector<PrimitiveSceneProxy*>* RenderProxyList)
{
	RenderBasePass(RenderProxyList);
}

void SimpleShadingRender::RenderBasePass(std::vector<PrimitiveSceneProxy*>* RenderProxyList)
{
	
	static float dtZ;
	static float speed = 0.001f;
	RHIClearRMT(mDefaultRenderTarget);
	RHIClearDepthView(mDefaultDepthRes);
	RHIOMPInputLayout(mDefualtInputLayout);
	RHISetPrimitiveTology(PrimitiveTopology::TRIANGLELIST);
	RHISetRasterizerState(mDefaultRasState);
	RHISetDepthState(mDefaultDepthState);
	RHISetBlendState(mDefaultBlendState);
	RHISetTextureSample(mDefaultTextureSampleState);
	/*RHIOMVSShader(mDefaultVertexShader);
	RHIOMPSShader(mDefaultPixelShader);*/
	{
		vRarelyCSB.dirLight[0].Ambient = XMFLOAT4(0.5f+dtZ, 0.5f + dtZ, 0.5f + dtZ, 1.0f + dtZ);
		RHIApplyConstantBuffer(mCBRarely, &vRarelyCSB, true);
		dtZ += speed;
		if (dtZ > 1.0f || dtZ< 0.0f)
		{
			speed = -1*speed;
		}
	}

	for (int i=0; i<RenderProxyList->size(); i++)
	{
		PrimitiveSceneProxy* vItemRender = (*RenderProxyList)[i];
		vItemRender->Draw(mCBDraw);
	}
	RHIPresent();
}
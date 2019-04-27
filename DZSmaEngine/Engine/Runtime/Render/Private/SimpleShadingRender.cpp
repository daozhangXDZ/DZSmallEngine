#include "SimpleShadingRender.h"
#include "EngineGlobal.h"
#include "D3D11/D3D11RHIResources.h"
#include "RHICommandList.h"
#include "RHIUtil.h"
#include "ShaderUtils.h"

void SimpleShadingRender::UpdateViewPort(RHICommandListImmediate* RHICMDList, ViewPortDesc* desc, bool isUpdateProj)
{
	if (isUpdateProj)
	{
		UpdateViewPortProjMat(RHICMDList,desc);
	}
	vFrameCSB.eyePos = XMLoadFloat3(&desc->eyepos);
	UpdateViewPortViewMat(RHICMDList,desc);
}

void SimpleShadingRender::UpdateViewPortViewMat(RHICommandListImmediate* RHICMDList, ViewPortDesc* desc)
{
	vFrameCSB.view = XMMatrixTranspose(desc->viewMat);
	RHIApplyConstantBuffer(RHICMDList->GetGlobalUniForm()->GetRHIFrameBuffer(),	&vFrameCSB, true);
}

void SimpleShadingRender::UpdateViewPortProjMat(RHICommandListImmediate* RHICMDList, ViewPortDesc* desc)
{
	vResizeCSB.proj = XMMatrixTranspose(desc->ProjMat);
	vResizeCSB.camera_N_F = desc->Near_Far;
	RHIApplyConstantBuffer(RHICMDList->GetGlobalUniForm()->GetRHIResizeBuffer(),  &vResizeCSB, true);
}

void SimpleShadingRender::SetCommandDepthBuffer()
{
	GDynamicRHI->SetRenderTarget(nullptr, GDynamicRHI->CreateDepthTarget(EPixelFormat::PF_D24));
	
}


void SimpleShadingRender::InitRes(RHICommandListImmediate* RHICMDList)
{
	//初始化灯光相关渲染资源
	{
		vRarelyCSB.reflection = XMMatrixTranspose(XMMatrixReflect(XMVectorSet(0.0f, 0.0f, -1.0f, 10.0f)));
		// 环境光
		for (int i =0; i< CEffect::maxDireLights; i++)
		{
			vRarelyCSB.dirLight[i].Ambient = XMFLOAT4(1.0f, 1.0f, 1.0f, 2.0f);
			vRarelyCSB.dirLight[i].Diffuse = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
			vRarelyCSB.dirLight[i].Specular = XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f);
			vRarelyCSB.dirLight[i].Direction = XMFLOAT3(-0.577f, -0.577f, 0.577f);
		}
		for (int i = 0,delfautPointLight = 3; i < CEffect::maxPointLights; i++)
		{
			vRarelyCSB.pointLight[i].Ambient = XMFLOAT4(1.0f, 0.5f, 0.5f, 0.5f);
			vRarelyCSB.pointLight[i].Diffuse = XMFLOAT4(0.3f, 0.3f, 0.3f, 1.0f);
			vRarelyCSB.pointLight[i].Specular = XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f);
			vRarelyCSB.pointLight[i].Position = XMFLOAT3(1+i*5.0f, 0.1f, 3.0f);
			vRarelyCSB.pointLight[i].Range = 10.0f;
		}
		RHIApplyConstantBuffer(RHICMDList->GetGlobalUniForm()->GetRHIRarelyBuffer(), &vRarelyCSB, true);
	}
	SetCommandDepthBuffer();
	mDepthDrawPolicy.Init();
	mBasePaseDrawPolicy.Init();
	mLightPassDrawPolicy.Init();
	mDebugPassPolicy.Init();
}



void SimpleShadingRender::Render(RHICommandListImmediate* RHICMDList, ISceneRenderInterface* RenderProxyList)
{
	// 测试 TODO 获取Light
	{
		static float dtZ;
		static float speed = 0.001f;
		vRarelyCSB.dirLight[0].Diffuse = XMFLOAT4(0.5f + dtZ, 0.5f + dtZ, 0.5f + dtZ, 1.0f);
		RHIApplyConstantBuffer(RHICMDList->GetGlobalUniForm()->GetRHIRarelyBuffer(), &vRarelyCSB, true);
		dtZ += speed;
		if (dtZ > 0.5f || dtZ < -0.5f)
		{
			speed = -1 * speed;
		}
	}
	RHIOMRenderTarget();
	RHIClearRMT();
	RHIOMViewPort(800.0f, 600.0f);
	RenderDepth(RHICMDList, RenderProxyList);
	RenderBasePass(RHICMDList,RenderProxyList);
	RenderLightPass(RHICMDList, RenderProxyList);
	RenderDebug(RHICMDList);
	RHIPresent();
}
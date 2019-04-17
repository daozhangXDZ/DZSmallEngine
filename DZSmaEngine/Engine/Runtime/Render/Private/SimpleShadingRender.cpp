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
	RHIApplyConstantBuffer(RHICMDList->GetGlobalUniForm()->GetRHIResizeBuffer(),  &vResizeCSB, true);
}


void SimpleShadingRender::InitRes(RHICommandListImmediate* RHICMDList)
{
	RHISetRenderTarget(RHICMDList->GetDefaultRendertarget());
	RHISetDepthTarget(RHICMDList->GetDefaultDepthtarget());
	RHIOMRenderTarget(RHICMDList->GetDefaultRendertarget(), RHICMDList->GetDefaultDepthtarget());
	//初始化灯光相关渲染资源
	{
		vRarelyCSB.reflection = XMMatrixTranspose(XMMatrixReflect(XMVectorSet(0.0f, 0.0f, -1.0f, 10.0f)));
		// 环境光
		vRarelyCSB.dirLight[0].Ambient = XMFLOAT4(0.5f, 0.5f, 0.5f, 0.5f);
		vRarelyCSB.dirLight[0].Diffuse = XMFLOAT4(0.3f, 0.3f, 0.3f, 1.0f);
		vRarelyCSB.dirLight[0].Specular = XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f);
		vRarelyCSB.dirLight[0].Direction = XMFLOAT3(-0.577f, -0.577f, 0.577f);
		/*vRarelyCSB.dirLight[1] = vRarelyCSB.dirLight[0];
		vRarelyCSB.dirLight[1].Direction = XMFLOAT3(0.577f, -0.577f, 0.577f);
		vRarelyCSB.dirLight[2] = vRarelyCSB.dirLight[0];
		vRarelyCSB.dirLight[2].Direction = XMFLOAT3(0.577f, -0.577f, -0.577f);
		vRarelyCSB.dirLight[3] = vRarelyCSB.dirLight[0];
		vRarelyCSB.dirLight[3].Direction = XMFLOAT3(-0.577f, -0.577f, -0.577f);*/
		RHIApplyConstantBuffer(RHICMDList->GetGlobalUniForm()->GetRHIRarelyBuffer(), &vRarelyCSB, true);
	}
	RHIOMViewPort(800.0f, 600.0f);
}



void SimpleShadingRender::Render(RHICommandListImmediate* RHICMDList, std::vector<PrimitiveSceneProxy*>* RenderProxyList)
{
	RenderBasePass(RHICMDList,RenderProxyList);
}

void SimpleShadingRender::RenderBasePass(RHICommandListImmediate* RHICMDList, std::vector<PrimitiveSceneProxy*>* RenderProxyList)
{
	
	static float dtZ;
	static float speed = 0.0001f;
	RHIClearRMT(RHICMDList->GetDefaultRendertarget());
	RHIClearDepthView(RHICMDList->GetDefaultDepthtarget());
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

	for (int i=0; i<RenderProxyList->size(); i++)
	{
		PrimitiveSceneProxy* vItemRender = (*RenderProxyList)[i];
		vItemRender->Draw(RHICMDList);
	}
	RHIPresent();
}
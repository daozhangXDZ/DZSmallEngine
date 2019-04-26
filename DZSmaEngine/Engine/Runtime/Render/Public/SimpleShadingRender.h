#pragma once
#include "SceneRender.h"
#include "DepthRender.h"
#include "BasePassRender.h"
#include "DebugPassRender.h"
class SimpleShadingRender :public SceneRender
{
public:
	virtual void InitRes(RHICommandListImmediate* RHICMDList)override;
	virtual void Render(RHICommandListImmediate* RHICMDList, ISceneRenderInterface* RenderProxyList) override;
	virtual void UpdateViewPort(RHICommandListImmediate* RHICMDList, ViewPortDesc* desc, bool isUpdateProj)override;
protected:
	void RenderDepth(RHICommandListImmediate* RHICMDList, ISceneRenderInterface* RenderScene);
	void RenderBasePass(RHICommandListImmediate* RHICMDList, ISceneRenderInterface* RenderScene);
	void RenderDebug(RHICommandListImmediate* RHICMDList);
	void UpdateViewPortViewMat(RHICommandListImmediate* RHICMDList, ViewPortDesc* desc)override;
	void UpdateViewPortProjMat(RHICommandListImmediate* RHICMDList, ViewPortDesc* desc)override;
	void SetCommandDepthBuffer();

private:
	CBChangesEveryFrame vFrameCSB;
	CBChangesOnResize vResizeCSB;
	CBChangesRarely vRarelyCSB;
	RHITexture2DRef mDepthTexture;
	RHIRenderTargetParamRef DepthRenderTargetViewParam;
	RHITexture2DRef mBasePassTexture;
	RHIRenderTargetParamRef BasePassRenderTargetViewParam;

	DepthRenderPolicy	mDepthDrawPolicy;
	BasePaseDrawPolicy	mBasePaseDrawPolicy;
	DebugShowPolicy		mDebugPassPolicy;
};
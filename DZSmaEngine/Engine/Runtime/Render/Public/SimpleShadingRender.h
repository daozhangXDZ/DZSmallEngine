#pragma once
#include "SceneRender.h"
class SimpleShadingRender :public SceneRender
{
public:
	virtual void InitRes(RHICommandListImmediate* RHICMDList)override;
	virtual void Render(RHICommandListImmediate* RHICMDList, std::vector<PrimitiveSceneProxy*>* RenderProxyList) override;
	virtual void UpdateViewPort(RHICommandListImmediate* RHICMDList, ViewPortDesc* desc, bool isUpdateProj)override;
protected:
	void RenderBasePass(RHICommandListImmediate* RHICMDList,  std::vector<PrimitiveSceneProxy*>* RenderProxyList);
	void UpdateViewPortViewMat(RHICommandListImmediate* RHICMDList, ViewPortDesc* desc)override;
	void UpdateViewPortProjMat(RHICommandListImmediate* RHICMDList, ViewPortDesc* desc)override;
	void SetCommandDepthBuffer();
private:
	CBChangesEveryFrame vFrameCSB;
	CBChangesOnResize vResizeCSB;
	CBChangesRarely vRarelyCSB;
};
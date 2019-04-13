#pragma once
#include "SceneRender.h"
class SimpleShadingRender :public SceneRender
{
public:
	virtual void InitRes()override;
	virtual void Render(std::vector<PrimitiveSceneProxy*>* RenderProxyList) override;
	virtual void UpdateViewPort(ViewPortDesc* desc, bool isUpdateProj)override;
protected:
	void RenderBasePass(std::vector<PrimitiveSceneProxy*>* RenderProxyList);
	void UpdateViewPortViewMat(ViewPortDesc* desc)override;
	void UpdateViewPortProjMat(ViewPortDesc* desc)override;
private:
	CBChangesEveryFrame vFrameCSB;
	CBChangesOnResize vResizeCSB;
	CBChangesRarely vRarelyCSB;
};
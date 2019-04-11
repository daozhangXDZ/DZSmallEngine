#pragma once
#include "SceneRender.h"
class SimpleShadingRender :public SceneRender
{
public:
	virtual void Render(std::vector<PrimitiveSceneProxy*>* RenderProxyList) override;
	virtual void UpdateViewProject(ViewPortDesc* desc, bool isUpdateProj) override;
protected:
	void RenderBasePass(std::vector<PrimitiveSceneProxy*>* RenderProxyList);
};
#pragma once
#include <vector>
#include "RenderProxy/primitivesceneproxy.h"
#include "ViewPortDesc.h"
using namespace std;
class SceneRender
{
public:
	
	SceneRender() {}
	virtual void Render(std::vector<PrimitiveSceneProxy*>* RenderProxyList) {};
	virtual void UpdateViewProject(ViewPortDesc* desc, bool isUpdateProj) {};
public:
	static SceneRender* GetShaderRender();
	
};
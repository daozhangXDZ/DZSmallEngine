#pragma once
#include <vector>
#include "ViewPortDesc.h"
#include "RHISources.h"
#include "RHIState.h"
#include "ISceneRenderInterface.h"
#include <map>
using namespace std;
class SceneRender
{
public:
	
	SceneRender() {}
	virtual void InitRes(RHICommandListImmediate* RHICMDList, ISceneRenderInterface* RenderProxyList) =0;
	virtual void Render(RHICommandListImmediate* RHICMDList, ISceneRenderInterface* RenderProxyList)=0;
	virtual void InitViewPort(RHICommandListImmediate* RHICMDList, RenderViewBoard ViewBoard) {};
	virtual void UpdateViewPort(RHICommandListImmediate* RHICMDList, ViewPortDesc* desc, bool isUpdateProj) {}

public:
	static SceneRender* GetShaderRender();
	
public:


protected:
	virtual void UpdateViewPortViewMat(RHICommandListImmediate* RHICMDList, ViewPortDesc* desc) = 0;

	virtual void UpdateViewPortProjMat(RHICommandListImmediate* RHICMDList, ViewPortDesc* desc) = 0;
};
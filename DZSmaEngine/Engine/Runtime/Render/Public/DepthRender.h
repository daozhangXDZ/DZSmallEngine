#pragma once
#include "RHISources.h"
#include "StaticMesh.h"
#include "DrawingPolicy.h"
/**
 * �����Ⱦ����
 */
class DepthRenderPolicy:public MeshDrawPolicy
{
public:
	RHIGraphicsPipelineStateInitializer gr;

public:
	virtual void Init();
	virtual void PreDraw(RHICommandListImmediate* RHICMDList, PrimitiveSceneInfo* component) override;
	virtual void SetupShaderState(RHICommandListImmediate* RHICMDList) override;
};
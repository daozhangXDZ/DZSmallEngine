#pragma once
#include "DrawingPolicy.h"
class BasePaseDrawPolicy :public MeshDrawPolicy
{
public:
	RHIGraphicsPipelineStateInitializer gr;
public:
	virtual void Init();
	virtual void PreDraw(RHICommandListImmediate* RHICMDList, PrimitiveSceneInfo* component) override;
	virtual void SetupShaderState(RHICommandListImmediate* RHICMDList) override;
};
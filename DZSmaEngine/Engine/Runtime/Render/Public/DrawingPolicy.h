#pragma once
#include "Components/PrimitiveComponent.h"
#include "PrimitiveSceneInfo.h"
#include "StaticMesh.h"
struct FDrawingPolicyRenderState
{

};

class MeshDrawPolicy
{
public:
	virtual void Init();
	virtual void PreDraw(RHICommandListImmediate* RHICMDList, PrimitiveSceneInfo* component);
	virtual void DrawMesh(RHICommandListImmediate* RHICMDList, PrimitiveSceneInfo* proxy);
	virtual void SetupShaderState(RHICommandListImmediate* RHICMDList) {};
};
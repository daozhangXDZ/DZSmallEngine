#pragma once
#include "RHISources.h"
#include "StaticMesh.h"
#include "RenderProxy/primitivesceneproxy.h"
/**
 * 深度渲染策略
 */
class DepthRenderPolicy
{
public:
	RHIVertexLayoutRef mVertexLayout;
	RHIVertexShaderRef mVertexShader;
	RHIPixelShaderRef  mPixelShader;

public:
	void DrawMesh(StaticMesh* mesh);
};

class FDepthDrawingPolicyFactory
{
public:
	/**
	 * 绘制
	 * 1、利用策略工厂根据需要产生策略
	 * 2、并设置相关状态，资源，
	 * 3、然后绘制
	 */
	static bool DrawMesh(
		RHICommandListImmediate* RHICmdList,
		StaticMesh* mesh,
		PrimitiveSceneProxy* PrimitiveSceneProxy
	);
};
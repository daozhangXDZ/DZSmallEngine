#pragma once
#include "RHISources.h"
#include "StaticMesh.h"
#include "RenderProxy/primitivesceneproxy.h"
/**
 * �����Ⱦ����
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
	 * ����
	 * 1�����ò��Թ���������Ҫ��������
	 * 2�����������״̬����Դ��
	 * 3��Ȼ�����
	 */
	static bool DrawMesh(
		RHICommandListImmediate* RHICmdList,
		StaticMesh* mesh,
		PrimitiveSceneProxy* PrimitiveSceneProxy
	);
};
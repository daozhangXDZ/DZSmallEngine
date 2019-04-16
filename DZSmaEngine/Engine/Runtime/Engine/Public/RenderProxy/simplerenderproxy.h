#pragma once
#include <d3d11.h>
#include <wrl/client.h>
#include <DirectXMath.h>
#include "RenderProxy/PrimitiveSceneProxy.h"
#include "D3D11/D3D11RHIResources.h"
#include <vector>

using namespace DirectX;

class SimpleMeshRenderProxy :public PrimitiveSceneProxy
{
public:
	

	RHIVertexBufferRef		mVertexBuffer = nullptr;
	RHIIndexBufferRef		mIndexBuffer = nullptr;

	std::vector<VertexPosNormalTangentTex> mVertexData;
	std::vector<DWORD> mIndexData;
	BaseMaterial* mainMaterial;
public:
	SimpleMeshRenderProxy();
	virtual void InitRender() override;
	virtual void SetupMainMaterial(BaseMaterial* pMainMateria) override;
	virtual void Draw(RHICommandListImmediate* pRHICmdList)override;
};
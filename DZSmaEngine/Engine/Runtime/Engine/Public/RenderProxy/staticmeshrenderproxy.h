#pragma once
#include <d3d11.h>
#include <wrl/client.h>
#pragma once
#include <d3d11.h>
#include <wrl/client.h>
#include <DirectXMath.h>
#include "RenderProxy/PrimitiveSceneProxy.h"
#include "D3D11/D3D11RHIResources.h"
#include <vector>


using namespace DirectX;


class StaticMeshSubRenderProxy :public PrimitiveSceneProxy
{
private:
	RHIVertexBufferRef		mVertexBuffer = nullptr;
	RHIIndexBufferRef		mIndexBuffer = nullptr;

public:
	std::vector<VertexPosNormalTangentTex> mVertexData;
	std::vector<DWORD> mIndexData;
	BaseMaterial* mainMaterial;
public:
	StaticMeshSubRenderProxy();
	virtual void SetupMainMaterial(BaseMaterial* pMainMateria) override;
	virtual void Draw(RHICommandListImmediate* pRHICmdList)override;
	virtual void InitRender() override;
};

class StaticMeshRenderProxy :public PrimitiveSceneProxy
{
public:
	std::vector<StaticMeshSubRenderProxy*> mSubMeshRenderList;
	std::vector<BaseMaterial*> materialNode;
public:
	StaticMeshRenderProxy();
	virtual void Draw(RHICommandListImmediate* pRHICmdList)override;
	virtual void InitRender() override;
};
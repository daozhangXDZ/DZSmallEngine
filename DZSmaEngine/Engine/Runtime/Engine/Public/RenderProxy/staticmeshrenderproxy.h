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
	RHIShaderResourceViewRef mMainTexture = nullptr;
	RHIVertexBufferRef		mVertexBuffer = nullptr;
	RHIIndexBufferRef		mIndexBuffer = nullptr;

public:
	std::wstring filePath;
	std::vector<VertexPosNormalTex> mVertexData;
	std::vector<DWORD> mIndexData;
	BaseMaterial* mainMaterial;
public:
	StaticMeshSubRenderProxy();
	virtual void SetupMainMaterial(BaseMaterial* pMainMateria) override;
	virtual void Draw(RHIUniFormBufferRef UniFormBuffer)override;
	virtual void InitRender() override;
};

class StaticMeshRenderProxy :public PrimitiveSceneProxy
{
private:
	RHIShaderResourceViewRef mMainTexture = nullptr;
public:
	std::vector<StaticMeshSubRenderProxy*> mSubMeshRenderList;
	std::vector<BaseMaterial*> materialNode;
	FWString filePath; //L"Data\\Textures\\p1.jpg"
public:
	StaticMeshRenderProxy();
	virtual void Draw(RHIUniFormBufferRef UniFormBuffer)override;
	virtual void InitRender() override;
};
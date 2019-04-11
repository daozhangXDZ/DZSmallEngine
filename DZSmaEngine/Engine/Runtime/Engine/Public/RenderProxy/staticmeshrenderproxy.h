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
	D3D11ShaderResourceViewRes * mMainTexture = nullptr;
	D3D11VertexBufferRes*		mVertexBuffer;
	D3D11IndexBufferRes*		mIndexBuffer;

public:
	std::wstring filePath;
	std::vector<VertexPosNormalTex> mVertexData;
	std::vector<DWORD> mIndexData;
	Material mMaterialDesc;

public:
	StaticMeshSubRenderProxy();
	virtual void Draw()override;
	virtual void InitRender() override;
};

class StaticMeshRenderProxy :public PrimitiveSceneProxy
{
private:
	D3D11ShaderResourceViewRes * mMainTexture = nullptr;
public:
	std::vector<StaticMeshSubRenderProxy*> mSubMeshRenderList;
	Material mMaterialDesc;
	FWString filePath; //L"Data\\Textures\\p1.jpg"
public:
	StaticMeshRenderProxy();
	virtual void Draw()override;
	virtual void InitRender() override;
};
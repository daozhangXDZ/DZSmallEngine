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
private:
	D3D11ShaderResourceViewRes* mMainTexture = nullptr;
public:
	/*BaseVertexBuffer<VertexPosNormalTex> mVertexBuffer;
	BaseIndexBuffer mIndexBuffer;*/
	D3D11VertexBufferRes*		mVertexBuffer;
	D3D11IndexBufferRes*		mIndexBuffer;

	std::wstring filePath; //L"Data\\Textures\\p1.jpg"
	std::vector<VertexPosNormalTex> mVertexData;
	std::vector<DWORD> mIndexData;

public:
	SimpleMeshRenderProxy();
	virtual void InitRender() override;
	virtual void Draw()override;
};
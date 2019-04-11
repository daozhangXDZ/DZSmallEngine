#include "LogUtil/ComException.h"
#include "LogUtil/ErrorLogger.h"
#include "RenderProxy/StaticMeshRenderProxy.h"
#include <WICTextureLoader.h>
#include "RHICommandList.h"

StaticMeshSubRenderProxy::StaticMeshSubRenderProxy()
{

}

void StaticMeshSubRenderProxy::InitRender()
{
	mMainTexture = new D3D11ShaderResourceViewRes();
	mVertexBuffer = new D3D11VertexBufferRes();
	mIndexBuffer = new D3D11IndexBufferRes();
	RHICreateVertexBuffer(mVertexBuffer,
		mVertexData.data(),
		sizeof(VertexPosNormalTex),
		mVertexData.size());

	RHICreateIndexBuffer(
		mIndexBuffer,
		mIndexData.data(),
		mIndexData.size()
	);

	RHICreateShaderResourcesView(
		mMainTexture,
		filePath
	);
}


void StaticMeshSubRenderProxy::Draw()
{
	XMMATRIX W = GetWorldMatrix();
	mCBDraw->world = XMMatrixTranspose(W);
	mCBDraw->worldInvTranspose = XMMatrixInverse(nullptr, W);
	mCBDraw->material.Ambient = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	mCBDraw->material.Diffuse = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	mCBDraw->material.Reflect = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	mCBDraw->material.Specular = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	RHIChangeConstanBuffer(mCBDraw, true);
	RHISetShaderResourcesView(0, 1, mMainTexture, D3D11ShaderType::PixelShader);
	RHIBindIndexBuffer(mIndexBuffer, 0, DXGI_FORMAT::DXGI_FORMAT_R32_UINT);
	UINT offset = 0;
	RHIBindVertexBuffer(mVertexBuffer, 0, 1, offset);
	RHIDrawIndexBuffer(mIndexBuffer, 0, 0);
}


//////////////////////////////////////////////////////////////////////////

StaticMeshRenderProxy::StaticMeshRenderProxy()
{

}

void StaticMeshRenderProxy::InitRender()
{
	for (int i = 0; i < mSubMeshRenderList.size(); i++)
	{
		mSubMeshRenderList[i]->SetupAttachComponent(this->parentComponent);
		mSubMeshRenderList[i]->InitRender();
	}
}


void StaticMeshRenderProxy::Draw()
{
	for (int i = 0; i < mSubMeshRenderList.size(); i++)
	{
		mSubMeshRenderList[i]->Draw();
	}
}
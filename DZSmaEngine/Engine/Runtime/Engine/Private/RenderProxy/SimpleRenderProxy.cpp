#include "LogUtil/ComException.h"
#include "LogUtil/ErrorLogger.h"
#include "RenderProxy/SimpleRenderProxy.h"
#include "RHICommandList.h"
#include <WICTextureLoader.h>

SimpleMeshRenderProxy::SimpleMeshRenderProxy()
	:PrimitiveSceneProxy()
{

}



void SimpleMeshRenderProxy::InitRender()
{

	////ห๗าýื้
	//HRESULT hr;
	//hr = this->mVertexBuffer.Initialize(this->device, mVertexData.data(), mVertexData.size());
	//COM_ERROR_IF_FAILED(hr, "Failed to initialize vertex buffer.");


	////Load Index Data
	//hr = this->mIndexBuffer.Initialize(this->device, mIndexData.data(), mIndexData.size());
	//COM_ERROR_IF_FAILED(hr, "Failed to initialize index buffer.");


	//const WCHAR * vLPPath = filePath.c_str();
	//hr = DirectX::CreateWICTextureFromFile(this->device, vLPPath, nullptr, &mMainTexture);
	//COM_ERROR_IF_FAILED(hr, "Failed to create wic texture from file.");
	mMainTexture = RHICreateShaderResourcesView(filePath);
	mVertexBuffer = RHICreateVertexBuffer(mVertexData.data(),
		sizeof(VertexPosNormalTex),
		mVertexData.size()
	);
	mIndexBuffer = RHICreateIndexBuffer(
		mIndexData.data(),
		mIndexData.size()
	);
}


void SimpleMeshRenderProxy::Draw(RHIUniFormBufferRef UniFormBuffer)
{
	XMMATRIX W = GetWorldMatrix();
	mCBDraw->world = XMMatrixTranspose(W);
	mCBDraw->worldInvTranspose = XMMatrixInverse(nullptr, W);
	mCBDraw->material.Ambient = XMFLOAT4(0.4f, 0.4f, 0.4f, 1.0f);
	mCBDraw->material.Diffuse = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
	mCBDraw->material.Specular = XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f);
	RHIChangeConstanBuffer(UniFormBuffer,mCBDraw,true);
	RHISetShaderRessourcesView(0,1,mMainTexture,EPipeLineFlag::PixelShader);
	RHIBindIndexBuffer(mIndexBuffer,0,DXGI_FORMAT::DXGI_FORMAT_R32_UINT);
	UINT offset = 0;
	RHIBindVertexBuffer(mVertexBuffer,0,1, offset);
	RHIDrawIndexBuffer(mIndexBuffer,0,0);
}
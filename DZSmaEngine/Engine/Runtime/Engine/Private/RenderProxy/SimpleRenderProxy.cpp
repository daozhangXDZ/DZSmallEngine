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


void SimpleMeshRenderProxy::Draw()
{
	XMMATRIX W = GetWorldMatrix();
	mCBDraw->world = XMMatrixTranspose(W);
	mCBDraw->worldInvTranspose = XMMatrixInverse(nullptr, W);
	mCBDraw->material.Ambient = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	mCBDraw->material.Diffuse = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	mCBDraw->material.Reflect = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	mCBDraw->material.Specular = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	RHIChangeConstanBuffer(mCBDraw,true);
	RHISetShaderResourcesView(0,1,mMainTexture,D3D11ShaderType::PixelShader);
	RHIBindIndexBuffer(mIndexBuffer,0,DXGI_FORMAT::DXGI_FORMAT_R32_UINT);
	UINT offset = 0;
	RHIBindVertexBuffer(mVertexBuffer,0,1, offset);
	RHIDrawIndexBuffer(mIndexBuffer,0,0);
	//if (this->mCBDraw->ApplyChanges())
	//{
	//	this->mCBDraw->RefreshBind();
	//}
	//if (this->mMainTexture != NULL)
	//{
	//	this->deviceContext->PSSetShaderResources(0, 1, &this->mMainTexture); //Set Texture
	//}
	//this->deviceContext->IASetIndexBuffer(this->mIndexBuffer.Get(), DXGI_FORMAT::DXGI_FORMAT_R32_UINT, 0);
	//UINT offset = 0;
	//this->deviceContext->IASetVertexBuffers(0, 1, this->mVertexBuffer.GetAddressOf(), this->mVertexBuffer.StridePtr(), &offset);
	//this->deviceContext->DrawIndexed(this->mIndexBuffer.BufferSize(), 0, 0); //Draw
}
#include "LogUtil/ComException.h"
#include "LogUtil/ErrorLogger.h"
#include "RenderProxy/StaticMeshRenderProxy.h"
#include <WICTextureLoader.h>
#include "RHICommandList.h"
#include "Material/MaterialUtils.h"

StaticMeshSubRenderProxy::StaticMeshSubRenderProxy()
{

}

void StaticMeshSubRenderProxy::SetupMainMaterial(BaseMaterial * pMainMateria)
{
	this->mainMaterial = pMainMateria;
}

void StaticMeshSubRenderProxy::InitRender()
{
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


void StaticMeshSubRenderProxy::Draw(RHIUniFormBufferRef UniFormBuffer)
{
	XMMATRIX W = GetWorldMatrix();
	mCBDraw->world = XMMatrixTranspose(W);
	mCBDraw->worldInvTranspose = XMMatrixInverse(nullptr, W);
	MaterialUtil::fillShaderMaterial(mainMaterial, &mCBDraw->material);
	RHIChangeConstanBuffer(UniFormBuffer, mCBDraw, true);
	RHISetShaderRessourcesView(0, 1, mMainTexture, EShaderFrequency::SF_Pixel);
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


void StaticMeshRenderProxy::Draw(RHIUniFormBufferRef UniFormBuffer)
{
	for (int i = 0; i < mSubMeshRenderList.size(); i++)
	{
		mSubMeshRenderList[i]->Draw(UniFormBuffer);
	}
}
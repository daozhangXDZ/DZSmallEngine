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
	mVertexBuffer = RHICreateVertexBuffer(mVertexData.data(),
		sizeof(VertexPosNormalTangentTex),
		mVertexData.size()
	);
	mIndexBuffer = RHICreateIndexBuffer(
		mIndexData.data(),
		mIndexData.size()
	);
}


void StaticMeshSubRenderProxy::Draw(RHICommandListImmediate* pRHICmdList)
{
	XMMATRIX W = GetWorldMatrix();
	mCBDraw->world = XMMatrixTranspose(W);
	mCBDraw->worldInvTranspose = XMMatrixInverse(nullptr, W);
	MaterialUtil::fillShaderMaterial(mainMaterial, &mCBDraw->material);
	RHIChangeConstanBuffer(pRHICmdList->GetGlobalUniForm()->GetRHIDrawBuffer(), mCBDraw, true);
	if (mainMaterial->mMainTexture != nullptr)
	{
		RHISetShaderRessourcesView(0, 1, mainMaterial->mMainTexture, EShaderFrequency::SF_Pixel);
	}
	if (mainMaterial->mNormalTexture != nullptr)
	{
		RHISetShaderRessourcesView(1, 1, mainMaterial->mNormalTexture, EShaderFrequency::SF_Pixel);
	}
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


void StaticMeshRenderProxy::Draw(RHICommandListImmediate* pRHICmdList)
{
	for (int i = 0; i < mSubMeshRenderList.size(); i++)
	{
		mSubMeshRenderList[i]->Draw(pRHICmdList);
	}
}
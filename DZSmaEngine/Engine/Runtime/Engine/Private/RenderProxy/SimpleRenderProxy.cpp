#include "LogUtil/ComException.h"
#include "LogUtil/ErrorLogger.h"
#include "RenderProxy/SimpleRenderProxy.h"
#include "RHICommandList.h"
#include <WICTextureLoader.h>
#include "Material/MaterialUtils.h"

SimpleMeshRenderProxy::SimpleMeshRenderProxy()
	:PrimitiveSceneProxy()
{

}



void SimpleMeshRenderProxy::InitRender()
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

void SimpleMeshRenderProxy::SetupMainMaterial(BaseMaterial * pMainMateria)
{
	mainMaterial = pMainMateria;
}


void SimpleMeshRenderProxy::Draw(RHICommandListImmediate* pRHICmdList)
{
	XMMATRIX W = GetWorldMatrix();
	mCBDraw->world = XMMatrixTranspose(W);
	mCBDraw->worldInvTranspose = XMMatrixInverse(nullptr, W);
	MaterialUtil::fillShaderMaterial(mainMaterial, &mCBDraw->material);
	RHIOMVSShader(mainMaterial->mVertexShader);
	RHIOMPSShader(mainMaterial->mPixelShader);
	RHIOMPInputLayout(mainMaterial->mInputLayout);
	RHISetPrimitiveTology(PrimitiveTopology::TRIANGLELIST);
	RHIChangeConstanBuffer(pRHICmdList->GetGlobalUniForm()->GetRHIDrawBuffer(),mCBDraw,true);
	if (mainMaterial->mMainTexture != nullptr)
	{
		RHISetShaderRessourcesView(0, 1, mainMaterial->mMainTexture, EShaderFrequency::SF_Pixel);
	}
	if (mainMaterial->mNormalTexture != nullptr)
	{
		RHISetShaderRessourcesView(1, 1, mainMaterial->mNormalTexture, EShaderFrequency::SF_Pixel);
	}
	RHIBindIndexBuffer(mIndexBuffer,0,DXGI_FORMAT::DXGI_FORMAT_R32_UINT);
	UINT offset = 0;
	RHIBindVertexBuffer(mVertexBuffer,0,1, offset);
	RHIDrawIndexBuffer(mIndexBuffer,0,0);
}
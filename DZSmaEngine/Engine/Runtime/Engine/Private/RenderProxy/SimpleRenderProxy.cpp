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

void SimpleMeshRenderProxy::SetupMainMaterial(BaseMaterial * pMainMateria)
{
	mainMaterial = pMainMateria;
}


void SimpleMeshRenderProxy::Draw(RHIUniFormBufferRef UniFormBuffer)
{
	XMMATRIX W = GetWorldMatrix();
	mCBDraw->world = XMMatrixTranspose(W);
	mCBDraw->worldInvTranspose = XMMatrixInverse(nullptr, W);
	MaterialUtil::fillShaderMaterial(mainMaterial, &mCBDraw->material);
	RHIOMVSShader(mainMaterial->mVertexShader);
	RHIOMPSShader(mainMaterial->mPixelShader);
	RHIOMPInputLayout(mainMaterial->mInputLayout);
	RHIChangeConstanBuffer(UniFormBuffer,mCBDraw,true);
	RHISetShaderRessourcesView(0,1,mMainTexture,EShaderFrequency::SF_Pixel);
	RHIBindIndexBuffer(mIndexBuffer,0,DXGI_FORMAT::DXGI_FORMAT_R32_UINT);
	UINT offset = 0;
	RHIBindVertexBuffer(mVertexBuffer,0,1, offset);
	RHIDrawIndexBuffer(mIndexBuffer,0,0);
}
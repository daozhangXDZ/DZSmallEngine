#include "DrawingPolicy.h"
#include "Material/MaterialUtils.h"

void MeshDrawPolicy::Init()
{
}

void MeshDrawPolicy::PreDraw(RHICommandListImmediate * RHICMDList, PrimitiveSceneInfo* pInfo)
{
	XMMATRIX W = pInfo->worldMaterix;
	CBChangesEveryDrawing* mCBDraw = new CBChangesEveryDrawing();
	mCBDraw->world = XMMatrixTranspose(W);
	mCBDraw->worldInvTranspose = XMMatrixInverse(nullptr, W);
	MaterialUtil::fillShaderMaterial(pInfo->materia, &mCBDraw->material);
	RHIChangeConstanBuffer(RHICMDList->GetGlobalUniForm()->GetRHIDrawBuffer(), mCBDraw, true);
}

void MeshDrawPolicy::DrawMesh(RHICommandListImmediate* RHICMDList, PrimitiveSceneInfo* pInfo)
{
	RHIBindIndexBuffer(pInfo->mesh->mIndexBuffer, 0, DXGI_FORMAT::DXGI_FORMAT_R32_UINT);
	UINT offset = 0;
	RHIBindVertexBuffer(pInfo->mesh->mVertexBuffer, 0, 1, offset);
	RHIDrawIndexBuffer(pInfo->mesh->mIndexBuffer, 0, 0);
}

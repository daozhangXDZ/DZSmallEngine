#include "RenderProxy/PrimitiveSceneProxy.h"

PrimitiveSceneProxy::PrimitiveSceneProxy()
{
	this->mCBDraw = new CBChangesEveryDrawing();
}

PrimitiveSceneProxy::~PrimitiveSceneProxy()
{
}

void PrimitiveSceneProxy::SetupAttachComponent(SceneComponent * attachCom)
{
	if (parentComponent != nullptr)
	{
		return;
	}
	parentComponent = attachCom;
}

void PrimitiveSceneProxy::InitRender()
{
	
}

DirectX::XMMATRIX PrimitiveSceneProxy::GetWorldMatrix()
{
	return this->parentComponent->GetWorldMaterix();
}

void PrimitiveSceneProxy::SetupMainMaterial(BaseMaterial * pMainMateria)
{
}

void PrimitiveSceneProxy::Draw(RHICommandListImmediate* pRHICmdList)
{

}

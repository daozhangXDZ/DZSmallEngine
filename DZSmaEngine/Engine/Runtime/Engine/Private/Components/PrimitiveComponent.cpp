#include "Components/PrimitiveComponent.h"

PrimitiveComponent::PrimitiveComponent():SceneComponent()
{

}

PrimitiveSceneProxy * PrimitiveComponent::getCurrRenderProxy()
{
	return mCurrRenderProxy;
}

void PrimitiveComponent::Initialize()
{
	this->mCurrRenderProxy = createRenderProxy();
	this->mCurrRenderProxy->SetupAttachComponent(this);
}

PrimitiveSceneProxy * PrimitiveComponent::createRenderProxy()
{
	return nullptr;
}


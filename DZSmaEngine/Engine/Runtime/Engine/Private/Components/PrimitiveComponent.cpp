#include "Components/PrimitiveComponent.h"

PrimitiveComponent::PrimitiveComponent():SceneComponent()
{
	SceneInfo = new PrimitiveSceneInfo();
}

void PrimitiveComponent::Initialize()
{
	
}

void PrimitiveComponent::Tick(float dt)
{
}

void PrimitiveComponent::UpdatePrimitiveSceneInfo()
{
}

PrimitiveSceneProxy * PrimitiveComponent::createRenderProxy()
{
	return new PrimitiveSceneProxy();
}

void PrimitiveComponent::UpdateSceneInfo()
{
}

PrimitiveSceneInfo * PrimitiveComponent::GetSceneInfo()
{
	return SceneInfo;
}


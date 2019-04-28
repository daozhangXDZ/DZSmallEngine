#include "Components/DirectionLightComponent.h"
#include "EngineGlobal.h"

DFVector DirectionLightComponent::GetDirection()
{
	return SceneComponent::GetRotationVector();
}

FSceneLightInfo * DirectionLightComponent::GetLightInfo()
{
	mLightInfo.Ambient = m_ambientColor;
	mLightInfo.Diffuse = m_diffuseColor;
	mLightInfo.Specular = m_specularColor;
	XMMATRIX camRotationMatrix = XMMatrixRotationRollPitchYaw(GetDirection().getX(), GetDirection().getY(), GetDirection().getZ());
	//Calculate unit vector of cam target based off camera forward value transformed by cam rotation matrix
	XMVECTOR camTarget = XMVector3TransformCoord(this->DEFAULT_FORWARD_VECTOR, camRotationMatrix);
	XMStoreFloat3(&mLightInfo.Direction, camTarget);
	mLightInfo.Etype = DirectionLight;
	mLightInfo.Position = GetPositionFloat3();
	GetViewXM(mLightInfo.view);
	GenerateProjectionMatrix(SCREEN_DEPTH, SCREEN_NEAR);
	GetProjXM(mLightInfo.proj);
	return &mLightInfo;
}


#include "Components/LightComponent.h"



void LightComponent::SetAmbientColor(float red, float green, float blue, float alpha)
{
	m_ambientColor = XMFLOAT4(red, green, blue, alpha);
	return;
}


void LightComponent::SetDiffuseColor(float red, float green, float blue, float alpha)
{
	m_diffuseColor = XMFLOAT4(red, green, blue, alpha);
	return;
}

XMFLOAT4 LightComponent::GetAmbientColor()
{
	return m_ambientColor;
}


XMFLOAT4 LightComponent::GetDiffuseColor()
{
	return m_diffuseColor;
}

void LightComponent::SetSpecularColor(float red, float green, float blue, float alpha)
{
	m_specularColor = XMFLOAT4(red, green, blue, alpha);
}

XMFLOAT4 LightComponent::GetSpecularColor()
{
	return m_specularColor;
}

float  LightComponent::GetLightIntensity()
{
	return lightIntensity;
}

void  LightComponent::SetLightIntensity(float pIntensity)
{
	lightIntensity = pIntensity;
}

DFVector  LightComponent::GetDirection()
{
	return DFVector(this->GetRotationVector());
}

void LightComponent::GetViewXM(DirectX::XMMATRIX& viewMatrix)
{
	XMMATRIX RotationMatrix = XMMatrixRotationRollPitchYaw(this->rot.x, this->rot.y, this->rot.z);
	XMVECTOR ForwardTarget = XMVector3TransformCoord(this->DEFAULT_FORWARD_VECTOR, RotationMatrix);
	ForwardTarget += posVector;
	XMVECTOR upDir = XMVector3TransformCoord(this->DEFAULT_UP_VECTOR, RotationMatrix);
	//Rebuild view matrix
	this->mlightViewMatrix = XMMatrixLookAtLH(this->posVector, ForwardTarget, upDir);
	viewMatrix = mlightViewMatrix;
}

void LightComponent::GenerateProjectionMatrix(float screenDepth, float screenNear)
{
	float fieldOfView, screenAspect;
	fieldOfView =  XM_PI * 0.5f;
	screenAspect = 1.0f;
	mlightProjectionMatrix = XMMatrixPerspectiveFovLH(fieldOfView, screenAspect, screenNear, screenDepth);
}

void  LightComponent::GetProjXM(DirectX::XMMATRIX& projectionMatrix)
{
	projectionMatrix = mlightProjectionMatrix;
}
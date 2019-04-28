#pragma once
#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "LightInfo.h"


class LightComponent :public SceneComponent
{

public:
	void SetAmbientColor(float red, float green, float blue, float alpha);
	XMFLOAT4 GetAmbientColor();
	void SetDiffuseColor(float red, float green, float blue, float alpha);
	XMFLOAT4 GetDiffuseColor();
	void SetSpecularColor(float red, float green, float blue, float alpha);
	XMFLOAT4 GetSpecularColor();
	float GetLightIntensity();
	void SetLightIntensity(float pIntensity);
	virtual DFVector GetDirection();

	void GetViewXM(DirectX::XMMATRIX& viewMatrix);
	virtual void GenerateProjectionMatrix(float, float);
	void GetProjXM(DirectX::XMMATRIX& projectionMatrix);

	virtual FSceneLightInfo* GetLightInfo() { return nullptr; };


protected:
	float lightIntensity = 3.0f;
	DirectX::XMFLOAT4 m_ambientColor;
	DirectX::XMFLOAT4 m_diffuseColor;
	DirectX::XMFLOAT4 m_specularColor;
	DirectX::XMMATRIX mlightViewMatrix;
	DirectX::XMMATRIX mlightProjectionMatrix;
	FSceneLightInfo mLightInfo;
};
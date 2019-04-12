#pragma once
#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
class LightComponent :public SceneComponent
{
private:
	float lightIntensity = 3.0f;
	DFVector lightColor = DFVector(0.0f, 0.0f, 0.0f);

public:
	DFVector  GetLightColor()
	{
		return lightColor;
	}
	void SetLightColor(DFVector pColor)
	{
		lightColor = pColor;
	}

	float GetLightIntensity()
	{
		return lightIntensity;
	}

	void SetLightIntensity(float pIntensity)
	{
		lightIntensity = pIntensity;
	}

	virtual DFVector GetDirection()
	{
		return DFVector(this->GetRotationVector());
	}
};
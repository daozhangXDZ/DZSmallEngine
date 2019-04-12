#pragma once
#include "LightComponent.h"
class DirectionLightComponent : public LightComponent
{
public:
	virtual DFVector GetDirection() override;
};
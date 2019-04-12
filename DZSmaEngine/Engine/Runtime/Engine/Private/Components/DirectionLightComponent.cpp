#include "Components/DirectionLightComponent.h"

DFVector DirectionLightComponent::GetDirection()
{
	return SceneComponent::GetRotationVector();
}


#pragma once
#include <d3d11.h>
#include <wrl/client.h>
#include <DirectXMath.h>
#include "Components/PrimitiveComponent.h"
#include "CoreMinimal.h"
/// <summary>
/// 引擎基础模型 如 Sphere - Cube - Panel - Cone
/// </summary>
class PanelMeshComponent :public PrimitiveComponent
{

public:
	PanelMeshComponent() {};

	BaseMaterial* mMainMaterial;
protected:
	virtual PrimitiveSceneProxy* createRenderProxy() override;

};
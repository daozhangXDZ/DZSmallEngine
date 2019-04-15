#pragma once
#include <d3d11.h>
#include <wrl/client.h>
#include <DirectXMath.h>
#include "Components/PrimitiveComponent.h"
#include "CoreMinimal.h"
/// <summary>
/// �������ģ�� �� Sphere - Cube - Panel - Cone
/// </summary>
class PanelMeshComponent :public PrimitiveComponent
{

private:
	FWString pPath;

public:
	PanelMeshComponent() {};

	PanelMeshComponent(FWString& pPath);
	BaseMaterial* mMainMaterial;
protected:
	virtual PrimitiveSceneProxy* createRenderProxy() override;

};
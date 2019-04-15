#pragma once
#include <d3d11.h>
#include <wrl/client.h>
#include <DirectXMath.h>
#include "Components/PrimitiveComponent.h"
#include "CoreMinimal.h"
/// <summary>
/// 引擎基础模型 如 Sphere - Cube - Panel - Cone
/// </summary>
class CubeMeshComponent:public PrimitiveComponent
{

private:
	FWString pPath;
public:
	CubeMeshComponent() = delete;

	CubeMeshComponent(FWString& pPath);
	BaseMaterial* mMainMaterial;
protected:
	virtual PrimitiveSceneProxy* createRenderProxy() override;

};
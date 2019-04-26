#pragma once
#include <d3d11.h>
#include <wrl/client.h>
#include <DirectXMath.h>
#include "Components/PrimitiveComponent.h"
#include "StaticMesh.h"
#include "CoreMinimal.h"
/// <summary>
/// �������ģ�� �� Sphere - Cube - Panel - Cone
/// </summary>
class CubeMeshComponent:public PrimitiveComponent
{
public:
	BaseMaterial* mMainMaterial;
	StaticMesh*   mMainMesh;
public:
	CubeMeshComponent();
	virtual void Initialize();
	virtual void Tick(float dt) override;
	virtual void UpdatePrimitiveSceneInfo();
	virtual PrimitiveSceneProxy* createRenderProxy();
	virtual void UpdateSceneInfo();
};
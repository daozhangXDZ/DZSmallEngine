#pragma once
#include <d3d11.h>
#include <wrl/client.h>
#include <DirectXMath.h>
#include "Components/SceneComponent.h"
#include "PrimitiveSceneProxy.h"
#include "PrimitiveSceneInfo.h"
#include "Material/Material.h"

class PrimitiveComponent :public SceneComponent
{
protected:
	PrimitiveSceneInfo* SceneInfo;
public:
	PrimitiveComponent();
	virtual void Initialize();
	virtual void Tick(float dt) override;
	virtual void UpdatePrimitiveSceneInfo();
	PrimitiveSceneInfo* GetSceneInfo();
	virtual PrimitiveSceneProxy* createRenderProxy();
	virtual void UpdateSceneInfo();
};
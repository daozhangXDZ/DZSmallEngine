#pragma once
#include <d3d11.h>
#include <wrl/client.h>
#include <DirectXMath.h>
#include "Components/SceneComponent.h"
#include "RenderProxy/PrimitiveSceneProxy.h"
#include "Material/Material.h"

class PrimitiveComponent :public SceneComponent
{
public:
	PrimitiveComponent();
	PrimitiveSceneProxy* getCurrRenderProxy();
	void Initialize();
protected:
	virtual PrimitiveSceneProxy* createRenderProxy();
protected:
	PrimitiveSceneProxy* mCurrRenderProxy = nullptr;
};
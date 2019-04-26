#pragma once
#include <d3d11.h>
#include <wrl/client.h>
#include <DirectXMath.h>
#include "VertexElementDesc.h"
#include "ConstantBufferTypes.h"
#include "Components/SceneComponent.h"
#include "RHISources.h"
#include "ShaderUtils.h"

class PrimitiveSceneProxy
{

protected:
	SceneComponent* parentComponent = nullptr;

private:
	bool isInit = false;
	

public:
	PrimitiveSceneProxy();
	~PrimitiveSceneProxy();
	virtual void Draw(RHICommandListImmediate* pRHICmdList);
};
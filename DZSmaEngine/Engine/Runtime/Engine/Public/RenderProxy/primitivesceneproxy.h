#pragma once
#include <d3d11.h>
#include <wrl/client.h>
#include <DirectXMath.h>
#include "VertexElementDesc.h"
#include "ConstantBufferTypes.h"
#include "Components/SceneComponent.h"
#include "RHISources.h"
#include "Material/Material.h"
#include "ShaderUtils.h"

class PrimitiveSceneProxy
{

protected:
	SceneComponent* parentComponent = nullptr;
	CBChangesEveryDrawing* mCBDraw;
private:
	bool isInit = false;
	

public:
	PrimitiveSceneProxy();
	~PrimitiveSceneProxy();

	void SetupAttachComponent(SceneComponent* attachCom);
	virtual void InitRender();
protected:
	DirectX::XMMATRIX GetWorldMatrix();
public:
	virtual void SetupMainMaterial(BaseMaterial* pMainMateria);
	virtual void Draw(RHICommandListImmediate* pRHICmdList);
};
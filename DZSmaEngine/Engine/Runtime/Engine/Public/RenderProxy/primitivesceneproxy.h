#pragma once
#include <d3d11.h>
#include <wrl/client.h>
#include <DirectXMath.h>
#include "VertexElementDesc.h"
#include "ConstantBufferTypes.h"
#include "Components/SceneComponent.h"


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

	virtual void Draw();
};
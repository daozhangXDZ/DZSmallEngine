#pragma once
#include <wrl/client.h>
#include "Components/SceneComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Components/CameraComponent.h"
#include "Components/LightComponent.h"
#include "Graphics/Graphics.h"
#include "ViewPortDesc.h"
#include <vector>
#include "Material/Material.h"
#include "ISceneRenderInterface.h"
//template<typename T>
class SceneProxy :public SceneComponent, public ISceneRenderInterface
{
public:
	SceneProxy();

	~SceneProxy() {};

	virtual bool initScene();

	virtual void Tick(float dt) override;

	void AddOneStaticPrimitiveComponent(PrimitiveComponent* obj);

	void AddOneDynamicPrimitiveComponent(PrimitiveComponent* obj);

	std::vector<PrimitiveComponent*> GetScenePrimitive();

	ViewPortDesc GetMainCameraDesc();

	virtual	TArray<PrimitiveSceneInfo*> GetDepthSceneInfoList() override;
	virtual TArray<PrimitiveSceneInfo*> GetBaseSceneInfoList() override;

	BaseCameraComponent* GetCamera();

protected:
	std::vector<PrimitiveComponent*>	__ObjList;
	std::vector<LightComponent*>		__LightList;
	BaseCameraComponent* mCameraComponent;
	ViewPortDesc mViewPortdesc;

	TArray<PrimitiveSceneInfo*>			SceneDepthInfo;
	TArray<PrimitiveSceneInfo*>			SceneRenderInfo;
};

extern SceneProxy* currCheckScene;

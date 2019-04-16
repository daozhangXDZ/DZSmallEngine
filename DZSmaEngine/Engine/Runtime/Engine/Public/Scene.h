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
//template<typename T>
class SceneProxy:public SceneComponent
{
public:
	SceneProxy();

	~SceneProxy() {};

	bool initScene();
	
	virtual void Tick(float dt) override;

	void AddOneStaticPrimitiveComponent(PrimitiveComponent* obj);
	
	void AddOneDynamicPrimitiveComponent(PrimitiveComponent* obj);

	std::vector<PrimitiveComponent*> GetScenePrimitive();

	ViewPortDesc GetMainCameraDesc();

	BaseCameraComponent* GetCamera()
	{
		return mCameraComponent;
	}

protected:
	void InitCamera();
	void InitMeshObj();
	void InitLight();

private:
	void InitCubeMode(XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 sca,  BaseMaterial* MainMaterial);
	void InitPanelMode(XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 sca,  BaseMaterial* MainMaterial);
	void InitSphereMode(XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 sca,  BaseMaterial* MainMaterial);
	void InitStaticMesh(XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 sca, std::string modelPath, BaseMaterial* MainMaterial);
private:
	std::vector<PrimitiveComponent*>	__ObjList;
	std::vector<LightComponent*>		__LightList;
	BaseCameraComponent* mCameraComponent;
	ViewPortDesc mViewPortdesc;
};
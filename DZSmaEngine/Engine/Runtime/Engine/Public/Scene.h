#pragma once
#include <wrl/client.h>
#include "Components/SceneComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Components/CameraComponent.h"
#include "Components/LightComponent.h"
#include "Graphics/Graphics.h"
#include "ViewPortDesc.h"
#include <vector>
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
	void InitExtendMode(XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 sca, std::string modelPath, std::wstring mainTexturePath, float pAlpha);
	void InitCubeMode(XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 sca, std::wstring mainTexturePath, float pAlpha);
	void InitPanelMode(XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 sca, std::wstring mainTexturePath, float pAlpha);
	void InitSphereMode(XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 sca, std::wstring mainTexturePath, float pAlpha);
	void InitStaticMesh(XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 sca, std::string modelPath, std::wstring mainTexturePath, float pAlpha);
	void InitStaticMesh(XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 sca, std::string modelPath, std::wstring mainTexturePath, float pAlpha, XMFLOAT4 Ambient, XMFLOAT4 Spec, XMFLOAT4 Diffcuse);

private:
	std::vector<PrimitiveComponent*>	__ObjList;
	std::vector<LightComponent*>		__LightList;
	BaseCameraComponent* mCameraComponent;
	ViewPortDesc mViewPortdesc;
};
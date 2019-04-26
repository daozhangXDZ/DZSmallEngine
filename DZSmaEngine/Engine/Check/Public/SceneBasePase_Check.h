#pragma once
#include "Scene.h"


class SceneTest01 :public SceneProxy
{
public:
	virtual bool initScene() override;
private:
	void InitCamera();
	void InitMeshObj();
	void InitLight();
	void InitCubeMode(XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 sca, BaseMaterial* MainMaterial);
	void InitPanelMode(XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 sca, BaseMaterial* MainMaterial);
	void InitSphereMode(XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 sca, BaseMaterial* MainMaterial);
	void InitStaticMesh(XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 sca, std::string modelPath, BaseMaterial* MainMaterial);
};
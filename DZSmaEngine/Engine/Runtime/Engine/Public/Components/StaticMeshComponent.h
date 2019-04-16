#pragma once
#include <d3d11.h>
#include <wrl/client.h>
#include "Components/PrimitiveComponent.h"
#include "RenderProxy/StaticMeshRenderProxy.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <vector>

using namespace DirectX;

class StaticMeshComponent :public PrimitiveComponent
{
public:
	BaseMaterial* mMainMaterial;
private: 
	//多个小模型
	std::vector<StaticMeshSubRenderProxy*> subProxyList;
	bool isLoadMeshed = false;
private:
	bool LoadModel(const std::string & mainTextureFilePath);
	void ProcessNode(aiNode * node, const aiScene * scene);
	StaticMeshSubRenderProxy* ProcessMesh(aiMesh * mesh, const aiScene * scene);
public:
	StaticMeshComponent() = delete;
	StaticMeshComponent(const std::string & modelPath);
	virtual void Tick(float dt) override;
protected:
	virtual PrimitiveSceneProxy* createRenderProxy() override;
};
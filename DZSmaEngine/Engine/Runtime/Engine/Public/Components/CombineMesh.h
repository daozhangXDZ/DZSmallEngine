//#pragma once
//#include <d3d11.h>
//#include <wrl/client.h>
//#include "Components/PrimitiveComponent.h"
//#include "D3D11/Buffer/ConstantBuffer.h"
//#include "D3D11/ConstantBufferTypes.h"
//#include "RenderProxy/PrimitiveSceneProxy.h"
//#include "RenderProxy/SimpleRenderProxy.h"
//#include <assimp/Importer.hpp>
//#include <assimp/postprocess.h>
//#include <assimp/scene.h>
//
//using namespace DirectX;
//
//
//class CombineMeshProxy :public PrimitiveSceneProxy
//{
//public:
//	CombineMeshProxy();
//	~CombineMeshProxy();
//	std::wstring filePath;
//private:
//	std::vector<SimpleMeshRenderProxy*> meshes;
//	ID3D11ShaderResourceView * mMainTexture = nullptr;
//
//public:
//	virtual void Init() override;
//
//	void Draw(XMMATRIX viewProjectionMatrix) override;
//public:
//	void addMesh(SimpleMeshRenderProxy* pMesh);
//	void setTexture(ID3D11ShaderResourceView * pt);
//};
//
//class CombineMeshComponent :public PrimitiveComponent
//{
//public:
//	std::wstring filePath;
//	float _selfRotSpeedZ = 1.0;
//	std::vector<SimpleMeshRenderProxy*> childProxy;
//private:
//	bool LoadModel(const std::string & filePath);
//	void ProcessNode(aiNode * node, const aiScene * scene);
//	SimpleMeshRenderProxy* ProcessMesh(aiMesh * mesh, const aiScene * scene);
//	ID3D11ShaderResourceView * texture = nullptr;
//
//
//public:
//	CombineMeshComponent();
//	CombineMeshComponent(const std::string & modelPath, const std::wstring & texturePath);
//	virtual void Tick(float dt) override;
//protected:
//	virtual PrimitiveSceneProxy* createRenderProxy() override;
//
//};
//

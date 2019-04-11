//#include "Components/CombineMesh.h"
//#include "LogUtil/COMException.h"
//#include "LogUtil/ErrorLogger.h"
//#include <WICTextureLoader.h>
//
//using namespace DirectX;
//
//CombineMeshComponent::CombineMeshComponent()
//{
//}
//
//CombineMeshComponent::CombineMeshComponent(const std::string & modelPath, const std::wstring & texturePath)
//{
//	try
//	{
//		filePath = texturePath;
//		if (!this->LoadModel(modelPath))
//			return;
//
//	}
//	catch (COMException & exception)
//	{
//		ErrorLogger::Log(exception);
//	}
//}
//
//void CombineMeshComponent::Tick(float dt)
//{
//	this->AdjustRotation(0.0f, _selfRotSpeedZ*dt, 0.0f);
//}
//
//PrimitiveSceneProxy * CombineMeshComponent::createRenderProxy()
//{
//	CombineMeshProxy* pcombine = new CombineMeshProxy();
//	for (int i = 0; i < childProxy.size(); i++)
//	{
//		pcombine->addMesh(childProxy[i]);
//	}
//	pcombine->filePath = filePath;
//	return pcombine;
//}
//
//
//
//bool CombineMeshComponent::LoadModel(const std::string & filePath)
//{
//	Assimp::Importer importer;
//
//	const aiScene* pScene = importer.ReadFile(filePath,
//												aiProcess_Triangulate |
//												aiProcess_ConvertToLeftHanded);
//
//	if (pScene == nullptr)
//		return false;
//
//	this->ProcessNode(pScene->mRootNode, pScene);
//	return true;
//}
//
//
//void CombineMeshComponent::ProcessNode(aiNode * node, const aiScene * scene)
//{
//	for (UINT i = 0; i < node->mNumMeshes; i++)
//	{
//		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
//	
//		SimpleMeshRenderProxy* vsingleProxy = ProcessMesh(mesh, scene);
//		childProxy.push_back(vsingleProxy);
//	}
//
//	for (UINT i = 0; i < node->mNumChildren; i++)
//	{
//		this->ProcessNode(node->mChildren[i], scene);
//	}
//}
//
//SimpleMeshRenderProxy* CombineMeshComponent::ProcessMesh(aiMesh * mesh, const aiScene * scene)
//{
//	// Data to fill
//	std::vector<VertexPosNormalTex> vertices;
//	std::vector<DWORD> indices;
//
//	//Get vertices
//	for (UINT i = 0; i < mesh->mNumVertices; i++)
//	{
//		VertexPosNormalTex vertex;
//
//		vertex.pos.x = mesh->mVertices[i].x;
//		vertex.pos.y = mesh->mVertices[i].y;
//		vertex.pos.z = mesh->mVertices[i].z;
//
//		if (mesh->mTextureCoords[0])
//		{
//			vertex.tex.x = (float)mesh->mTextureCoords[0][i].x;
//			vertex.tex.y = (float)mesh->mTextureCoords[0][i].y;
//		}
//
//		vertices.push_back(vertex);
//	}
//
//	//Get indices
//	for (UINT i = 0; i < mesh->mNumFaces; i++)
//	{
//		aiFace face = mesh->mFaces[i];
//
//		for (UINT j = 0; j < face.mNumIndices; j++)
//			indices.push_back(face.mIndices[j]);
//	}
//
//	SimpleMeshRenderProxy* vpro = new SimpleMeshRenderProxy();
//	vpro->mVertexData = vertices;
//	vpro->mIndexData = indices;
//	return vpro;
//}
//
//
//
//
//
//
//
//CombineMeshProxy::CombineMeshProxy()
//{
//}
//
//CombineMeshProxy::~CombineMeshProxy()
//{
//}
//
//void CombineMeshProxy::Init()
//{
//	const WCHAR * vLPPath = filePath.c_str();
//	HRESULT hr = DirectX::CreateWICTextureFromFile(this->device, vLPPath, nullptr, &mMainTexture);
//	COM_ERROR_IF_FAILED(hr, "Failed to create wic texture from file.");
//	for (int i = 0; i < meshes.size(); i++)
//	{
//		meshes[i]->SetupAttachComponent(this->parentComponent);
//		meshes[i]->filePath = this->filePath;
//		meshes[i]->SetupRender(this->device, this->deviceContext, this->mCBDraw);
//	}
//}
//
//void CombineMeshProxy::Draw(XMMATRIX viewProjectionMatrix)
//{
//	//Update Constant buffer with WVP Matrix
//	for (int i = 0; i < meshes.size(); i++)
//	{
//		meshes[i]->Draw(viewProjectionMatrix);
//	}
//}
//
//void CombineMeshProxy::addMesh(SimpleMeshRenderProxy* pMesh)
//{
//	meshes.push_back(pMesh);
//}
//
//void CombineMeshProxy::setTexture(ID3D11ShaderResourceView * pt)
//{
//	mMainTexture = pt;
//}

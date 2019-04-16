#include "Components/StaticMeshComponent.h"
#include "RenderProxy/StaticMeshRenderProxy.h"
#include "LogUtil/COMException.h"
#include "LogUtil/ErrorLogger.h"

StaticMeshComponent::StaticMeshComponent(const std::string & modelPath)
{
	try
	{
		if (!this->LoadModel(modelPath))
			return;

	}
	catch (COMException & exception)
	{
		ErrorLogger::Log(exception);
	}
}

void StaticMeshComponent::Tick(float dt)
{
}

bool StaticMeshComponent::LoadModel(const std::string & mainTextureFilePath)
{
	Assimp::Importer importer;

	const aiScene* pScene = importer.ReadFile(mainTextureFilePath,
		aiProcess_Triangulate |
		aiProcess_ConvertToLeftHanded);

	if (pScene == nullptr)
		return false;

	this->ProcessNode(pScene->mRootNode, pScene);
	isLoadMeshed = true;
	return true;
}

void StaticMeshComponent::ProcessNode(aiNode * node, const aiScene * scene)
{
	for (UINT i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];

		StaticMeshSubRenderProxy* vsingleProxy = ProcessMesh(mesh, scene);
		subProxyList.push_back(vsingleProxy);
	}

	for (UINT i = 0; i < node->mNumChildren; i++)
	{
		this->ProcessNode(node->mChildren[i], scene);
	}
}

StaticMeshSubRenderProxy * StaticMeshComponent::ProcessMesh(aiMesh * mesh, const aiScene * scene)
{
	// Data to fill
	StaticMeshSubRenderProxy* vSubProxy = new StaticMeshSubRenderProxy();
	std::vector<VertexPosNormalTangentTex> vertices;
	std::vector<DWORD> indices;
	//Get vertices
	for (UINT i = 0; i < mesh->mNumVertices; i++)
	{
		VertexPosNormalTangentTex vertex;

		vertex.pos.x = mesh->mVertices[i].x;
		vertex.pos.y = mesh->mVertices[i].y;
		vertex.pos.z = mesh->mVertices[i].z;

		if (mesh->mTextureCoords[0])
		{
			vertex.tex.x = (float)mesh->mTextureCoords[0][i].x;
			vertex.tex.y = (float)mesh->mTextureCoords[0][i].y;
		}
		vertices.push_back(vertex);
	}

	//Get indices
	for (UINT i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];

		for (UINT j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}
	vSubProxy->mVertexData = vertices;
	vSubProxy->mIndexData = indices;
	return vSubProxy;
}



PrimitiveSceneProxy * StaticMeshComponent::createRenderProxy()
{
	StaticMeshRenderProxy* vMeshRenderProxy = new StaticMeshRenderProxy();
	for (int i=0; i< subProxyList.size(); i++)
	{
		subProxyList[i]->SetupMainMaterial(this->mMainMaterial);
		vMeshRenderProxy->mSubMeshRenderList.push_back(subProxyList[i]);
	}
	return vMeshRenderProxy;
}

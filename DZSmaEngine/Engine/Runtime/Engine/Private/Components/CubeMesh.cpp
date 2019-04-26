#include "Components/CubeMesh.h"
#include "Geometry.h"

CubeMeshComponent::CubeMeshComponent()
{

}

void CubeMeshComponent::Initialize()
{
	SceneInfo->materia = mMainMaterial;
	
	SceneInfo->mesh = new StaticMesh();
	{
		Geometry::MeshData<VertexPosNormalTangentTex, DWORD> meshdatt;
		meshdatt = Geometry::CreateBox<VertexPosNormalTangentTex, DWORD>();
		SceneInfo->mesh->mIndexData = meshdatt.indexVec;
		SceneInfo->mesh->mVertexData = meshdatt.vertexVec;
		SceneInfo->mesh->InitRHI();
	}
	SceneInfo->RenderProxy = createRenderProxy();
	SceneInfo->worldMaterix = GetWorldMaterix();
}

void CubeMeshComponent::Tick(float dt)
{

}

void CubeMeshComponent::UpdatePrimitiveSceneInfo()
{

}

PrimitiveSceneProxy* CubeMeshComponent::createRenderProxy()
{ 
	return new PrimitiveSceneProxy();
}

void CubeMeshComponent::UpdateSceneInfo()
{

}

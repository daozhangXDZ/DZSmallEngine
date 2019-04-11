#include "Components/CubeMesh.h"
#include "RenderProxy/SimpleRenderProxy.h"
#include "Geometry.h"

CubeMeshComponent::CubeMeshComponent(FWString& pPath)
{
	this->pPath = pPath;
}

PrimitiveSceneProxy* CubeMeshComponent::createRenderProxy()
{
	SimpleMeshRenderProxy* proxy = new SimpleMeshRenderProxy();
	Geometry::MeshData<VertexPosNormalTex, DWORD> meshdatt;
	meshdatt = Geometry::CreateBox<VertexPosNormalTex, DWORD>();
	proxy->filePath = this->pPath;
	proxy->mIndexData = meshdatt.indexVec;
	proxy->mVertexData = meshdatt.vertexVec;
	return proxy;
}

#include "Components/CubeMesh.h"
#include "RenderProxy/SimpleRenderProxy.h"
#include "Geometry.h"

CubeMeshComponent::CubeMeshComponent()
{

}

PrimitiveSceneProxy* CubeMeshComponent::createRenderProxy()
{
	SimpleMeshRenderProxy* proxy = new SimpleMeshRenderProxy();
	Geometry::MeshData<VertexPosNormalTangentTex, DWORD> meshdatt;
	meshdatt = Geometry::CreateBox<VertexPosNormalTangentTex, DWORD>();
	proxy->SetupMainMaterial(mMainMaterial);
	proxy->mIndexData = meshdatt.indexVec;
	proxy->mVertexData = meshdatt.vertexVec;
	return proxy;
}

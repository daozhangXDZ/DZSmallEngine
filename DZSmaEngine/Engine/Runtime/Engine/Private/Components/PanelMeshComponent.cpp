#include "Components/PanelMeshComponent.h"
#include "RenderProxy/SimpleRenderProxy.h"
#include "Geometry.h"

PrimitiveSceneProxy* PanelMeshComponent::createRenderProxy()
{
	SimpleMeshRenderProxy* proxy = new SimpleMeshRenderProxy();
	Geometry::MeshData<VertexPosNormalTangentTex, DWORD> meshdatt;
	meshdatt = Geometry::CreatePlane<VertexPosNormalTangentTex, DWORD>();
	proxy->SetupMainMaterial(mMainMaterial);
	proxy->mIndexData = meshdatt.indexVec;
	proxy->mVertexData = meshdatt.vertexVec;
	return proxy;
}

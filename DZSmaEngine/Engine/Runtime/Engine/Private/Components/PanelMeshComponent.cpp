#include "Components/PanelMeshComponent.h"
#include "RenderProxy/SimpleRenderProxy.h"
#include "Geometry.h"

PanelMeshComponent::PanelMeshComponent(FWString& pPath)
{
	this->pPath = pPath;
}

PrimitiveSceneProxy* PanelMeshComponent::createRenderProxy()
{
	SimpleMeshRenderProxy* proxy = new SimpleMeshRenderProxy();
	Geometry::MeshData<VertexPosNormalTex, DWORD> meshdatt;
	meshdatt = Geometry::CreatePlane<VertexPosNormalTex, DWORD>();
	proxy->SetupMainMaterial(mMainMaterial);
	proxy->filePath = this->pPath;
	proxy->mIndexData = meshdatt.indexVec;
	proxy->mVertexData = meshdatt.vertexVec;
	return proxy;
}

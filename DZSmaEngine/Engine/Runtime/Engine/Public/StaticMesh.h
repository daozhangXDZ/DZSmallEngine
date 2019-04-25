#pragma once
#include "StaticMeshVertexBuffer.h"
#include "RenderResource.h"
#include "VertexElementDesc.h"
#include "Material/Material.h"
class StaticMesh
{
	RHIVertexBufferRef		mVertexBuffer = nullptr;
	RHIIndexBufferRef		mIndexBuffer = nullptr;

	std::vector<VertexPosNormalTangentTex> mVertexData;
	std::vector<DWORD> mIndexData;
	BaseMaterial* mainMaterial;
};
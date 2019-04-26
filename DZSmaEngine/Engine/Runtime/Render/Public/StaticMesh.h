#pragma once
#include "StaticMeshVertexBuffer.h"
#include "RenderResource.h"
#include "VertexElementDesc.h"
#include "Material/Material.h"
class StaticMesh
{
public:
	RHIVertexBufferRef		mVertexBuffer = nullptr;
	RHIIndexBufferRef		mIndexBuffer = nullptr;

	std::vector<VertexPosNormalTangentTex> mVertexData;
	std::vector<DWORD> mIndexData;
	BaseMaterial* mainMaterial;

public:
	void InitRHI()
	{
		mVertexBuffer = RHICreateVertexBuffer(mVertexData.data(),
			sizeof(VertexPosNormalTangentTex),
			(UINT)mVertexData.size()
		);
		mIndexBuffer = RHICreateIndexBuffer(
			mIndexData.data(),
			(UINT)mIndexData.size()
		);

	}

	void ReleaseRHI()
	{

	}
};
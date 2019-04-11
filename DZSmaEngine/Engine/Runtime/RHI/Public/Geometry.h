//***************************************************************************************
// Geometry.h by X_Jun(MKXJun) (C) 2018-2019 All Rights Reserved.
// Licensed under the MIT License.
//
// ���ɳ����ļ���������ģ��
// Generate common geometry meshes.
//***************************************************************************************

#ifndef GEOMETRY_H_
#define GEOMETRY_H_

#include <vector>
#include <string>
#include <map>
#include "VertexElementDesc.h"

class Geometry
{
public:
	// ��������
	template<class VertexType = VertexPosNormalTex, class IndexType = WORD>
	struct MeshData
	{
		std::vector<VertexType> vertexVec;	// ��������
		std::vector<IndexType> indexVec;	// ��������

		MeshData()
		{
			// ������������ͺϷ���
			static_assert(sizeof(IndexType) == 2 || sizeof(IndexType) == 4, "The size of IndexType must be 2 bytes or 4 bytes!");
			static_assert(std::is_unsigned<IndexType>::value, "IndexType must be unsigned integer!");
		}
	};

	// ���������������ݣ�levels��slicesԽ�󣬾���Խ�ߡ�
	template<class VertexType = VertexPosNormalTex, class IndexType = WORD>
	static MeshData<VertexType, IndexType> CreateSphere(float radius = 1.0f, int levels = 20, int slices = 20,
		const DirectX::XMFLOAT4& color = { 1.0f, 1.0f, 1.0f, 1.0f });


	// ������������������
	template<class VertexType = VertexPosNormalTex, class IndexType = WORD>
	static MeshData<VertexType, IndexType> CreateBox(float width = 2.0f, float height = 2.0f, float depth = 2.0f,
		const DirectX::XMFLOAT4& color = { 1.0f, 1.0f, 1.0f, 1.0f });

	// ����Բ�����������ݣ�slicesԽ�󣬾���Խ�ߡ�
	template<class VertexType = VertexPosNormalTex, class IndexType = WORD>
	static MeshData<VertexType, IndexType> CreateCylinder(float radius = 1.0f, float height = 2.0f, int slices = 20,
		const DirectX::XMFLOAT4& color = { 1.0f, 1.0f, 1.0f, 1.0f });



	// ����ֻ��Բ���������������ݣ�slicesԽ�󣬾���Խ��
	template<class VertexType = VertexPosNormalTex, class IndexType = WORD>
	static MeshData<VertexType, IndexType> CreateCylinderNoCap(float radius = 1.0f, float height = 2.0f, int slices = 20,
		const DirectX::XMFLOAT4& color = { 1.0f, 1.0f, 1.0f, 1.0f });

	// ����һ������NDC��Ļ����
	template<class VertexType = VertexPosTex, class IndexType = WORD>
	static MeshData<VertexType, IndexType> Create2DShow(const DirectX::XMFLOAT2& center, const DirectX::XMFLOAT2& scale = { 1.0f, 1.0f },
		const DirectX::XMFLOAT4& color = { 1.0f, 1.0f, 1.0f, 1.0f });
	template<class VertexType = VertexPosTex, class IndexType = WORD>
	static MeshData<VertexType, IndexType> Create2DShow(float centerX = 0.0f, float centerY = 0.0f, float scaleX = 1.0f, float scaleY = 1.0f,
		const DirectX::XMFLOAT4& color = { 1.0f, 1.0f, 1.0f, 1.0f });

	// ����һ��ƽ��
	template<class VertexType = VertexPosNormalTex, class IndexType = WORD>
	static MeshData<VertexType, IndexType> CreatePlane(const DirectX::XMFLOAT3& center, const DirectX::XMFLOAT2& planeSize = { 10.0f, 10.0f },
		const DirectX::XMFLOAT2& maxTexCoord = { 1.0f, 1.0f }, const DirectX::XMFLOAT4& color = { 1.0f, 1.0f, 1.0f, 1.0f });
	template<class VertexType = VertexPosNormalTex, class IndexType = WORD>
	static MeshData<VertexType, IndexType> CreatePlane(float centerX = 0.0f, float centerY = 0.0f, float centerZ = 0.0f,
		float width = 10.0f, float depth = 10.0f, float texU = 1.0f, float texV = 1.0f,
		const DirectX::XMFLOAT4& color = { 1.0f, 1.0f, 1.0f, 1.0f });

private:
	struct VertexData
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT3 normal;
		DirectX::XMFLOAT4 tangent;
		DirectX::XMFLOAT4 color;
		DirectX::XMFLOAT2 tex;
	};

	template<class VertexType>
	static void InsertVertexElement(VertexType& vertexDst, const VertexData& vertexSrc);

private:
	static const std::map<std::string, std::pair<size_t, size_t>> semanticSizeMap;
};






//
// �����巽����ʵ��
//

// ����Ŀ�궥������ѡ���Խ����ݲ���
template<class VertexType>
inline void Geometry::InsertVertexElement(VertexType& vertexDst, const VertexData& vertexSrc)
{
	static std::string semanticName;
	for (size_t i = 0; i < ARRAYSIZE(VertexType::inputLayout); i++)
	{
		semanticName = VertexType::inputLayout[i].SemanticName;
		const auto& range = Geometry::semanticSizeMap.at(semanticName);
		memcpy_s(reinterpret_cast<char*>(&vertexDst) + VertexType::inputLayout[i].AlignedByteOffset,
			range.second - range.first,
			reinterpret_cast<const char*>(&vertexSrc) + range.first,
			range.second - range.first);
	}
}


template<class VertexType, class IndexType>
inline Geometry::MeshData<VertexType, IndexType> Geometry::CreateSphere(float radius, int levels, int slices, const DirectX::XMFLOAT4 & color)
{
	using namespace DirectX;

	constexpr size_t NumElems = ARRAYSIZE(VertexType::inputLayout);

	MeshData<VertexType, IndexType> meshData;
	meshData.vertexVec.resize(2 + (levels - 1) * (slices + 1));
	meshData.indexVec.resize(6 * (levels - 1) * slices);

	VertexData vertexData;
	IndexType vIndex = 0, iIndex = 0;

	float phi = 0.0f, theta = 0.0f;
	float per_phi = XM_PI / levels;
	float per_theta = XM_2PI / slices;
	float x, y, z;

	// ���붥�˵�
	vertexData = { XMFLOAT3(0.0f, radius, 0.0f), XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), color, XMFLOAT2(0.0f, 0.0f) };
	InsertVertexElement(meshData.vertexVec[vIndex++], vertexData);

	for (int i = 1; i < levels; ++i)
	{
		phi = per_phi * i;
		// ��Ҫslices + 1����������Ϊ �����յ���Ϊͬһ�㣬����������ֵ��һ��
		for (int j = 0; j <= slices; ++j)
		{
			theta = per_theta * j;
			x = radius * sinf(phi) * cosf(theta);
			y = radius * cosf(phi);
			z = radius * sinf(phi) * sinf(theta);
			// ������ֲ����ꡢ��������Tangent��������������
			XMFLOAT3 pos = XMFLOAT3(x, y, z), normal;
			XMStoreFloat3(&normal, XMVector3Normalize(XMLoadFloat3(&pos)));

			vertexData = { pos, normal, XMFLOAT4(-sinf(theta), 0.0f, cosf(theta), 1.0f), color, XMFLOAT2(theta / XM_2PI, phi / XM_PI) };
			InsertVertexElement(meshData.vertexVec[vIndex++], vertexData);
		}
	}

	// ����׶˵�
	vertexData = { XMFLOAT3(0.0f, -radius, 0.0f), XMFLOAT3(0.0f, -1.0f, 0.0f),
		XMFLOAT4(-1.0f, 0.0f, 0.0f, 1.0f), color, XMFLOAT2(0.0f, 1.0f) };
	InsertVertexElement(meshData.vertexVec[vIndex++], vertexData);


	// �𽥷�������
	if (levels > 1)
	{
		for (int j = 1; j <= slices; ++j)
		{
			meshData.indexVec[iIndex++] = 0;
			meshData.indexVec[iIndex++] = j % (slices + 1) + 1;
			meshData.indexVec[iIndex++] = j;
		}
	}


	for (int i = 1; i < levels - 1; ++i)
	{
		for (int j = 1; j <= slices; ++j)
		{
			meshData.indexVec[iIndex++] = (i - 1) * (slices + 1) + j;
			meshData.indexVec[iIndex++] = (i - 1) * (slices + 1) + j % (slices + 1) + 1;
			meshData.indexVec[iIndex++] = i * (slices + 1) + j % (slices + 1) + 1;

			meshData.indexVec[iIndex++] = i * (slices + 1) + j % (slices + 1) + 1;
			meshData.indexVec[iIndex++] = i * (slices + 1) + j;
			meshData.indexVec[iIndex++] = (i - 1) * (slices + 1) + j;
		}
	}

	// �𽥷�������
	if (levels > 1)
	{
		for (int j = 1; j <= slices; ++j)
		{
			meshData.indexVec[iIndex++] = (levels - 2) * (slices + 1) + j;
			meshData.indexVec[iIndex++] = (levels - 2) * (slices + 1) + j % (slices + 1) + 1;
			meshData.indexVec[iIndex++] = (levels - 1) * (slices + 1) + 1;
		}
	}


	return meshData;
}

template<class VertexType, class IndexType>
inline Geometry::MeshData<VertexType, IndexType> Geometry::CreateBox(float width, float height, float depth, const DirectX::XMFLOAT4 & color)
{
	using namespace DirectX;

	MeshData<VertexType, IndexType> meshData;
	meshData.vertexVec.resize(24);


	VertexData vertexDataArr[24];
	float w2 = width / 2, h2 = height / 2, d2 = depth / 2;


	// ����
	vertexDataArr[0].pos = XMFLOAT3(-w2, h2, -d2);
	vertexDataArr[1].pos = XMFLOAT3(-w2, h2, d2);
	vertexDataArr[2].pos = XMFLOAT3(w2, h2, d2);
	vertexDataArr[3].pos = XMFLOAT3(w2, h2, -d2);
	// ����
	vertexDataArr[4].pos = XMFLOAT3(w2, -h2, -d2);
	vertexDataArr[5].pos = XMFLOAT3(w2, -h2, d2);
	vertexDataArr[6].pos = XMFLOAT3(-w2, -h2, d2);
	vertexDataArr[7].pos = XMFLOAT3(-w2, -h2, -d2);
	// ����
	vertexDataArr[8].pos = XMFLOAT3(-w2, -h2, d2);
	vertexDataArr[9].pos = XMFLOAT3(-w2, h2, d2);
	vertexDataArr[10].pos = XMFLOAT3(-w2, h2, -d2);
	vertexDataArr[11].pos = XMFLOAT3(-w2, -h2, -d2);
	// ����
	vertexDataArr[12].pos = XMFLOAT3(w2, -h2, -d2);
	vertexDataArr[13].pos = XMFLOAT3(w2, h2, -d2);
	vertexDataArr[14].pos = XMFLOAT3(w2, h2, d2);
	vertexDataArr[15].pos = XMFLOAT3(w2, -h2, d2);
	// ǰ��
	vertexDataArr[16].pos = XMFLOAT3(w2, -h2, d2);
	vertexDataArr[17].pos = XMFLOAT3(w2, h2, d2);
	vertexDataArr[18].pos = XMFLOAT3(-w2, h2, d2);
	vertexDataArr[19].pos = XMFLOAT3(-w2, -h2, d2);
	// ����
	vertexDataArr[20].pos = XMFLOAT3(-w2, -h2, -d2);
	vertexDataArr[21].pos = XMFLOAT3(-w2, h2, -d2);
	vertexDataArr[22].pos = XMFLOAT3(w2, h2, -d2);
	vertexDataArr[23].pos = XMFLOAT3(w2, -h2, -d2);

	for (int i = 0; i < 4; ++i)
	{
		vertexDataArr[i].normal = XMFLOAT3(0.0f, 1.0f, 0.0f);		// ����
		vertexDataArr[i].tangent = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
		vertexDataArr[i].color = color;

		vertexDataArr[i + 4].normal = XMFLOAT3(0.0f, -1.0f, 0.0f);	// ����
		vertexDataArr[i + 4].tangent = XMFLOAT4(-1.0f, 0.0f, 0.0f, 1.0f);
		vertexDataArr[i + 4].color = color;

		vertexDataArr[i + 8].normal = XMFLOAT3(-1.0f, 0.0f, 0.0f);	// ����
		vertexDataArr[i + 8].tangent = XMFLOAT4(0.0f, 0.0f, -1.0f, 1.0f);
		vertexDataArr[i + 8].color = color;

		vertexDataArr[i + 12].normal = XMFLOAT3(1.0f, 0.0f, 0.0f);	// ����
		vertexDataArr[i + 12].tangent = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);
		vertexDataArr[i + 12].color = color;

		vertexDataArr[i + 16].normal = XMFLOAT3(0.0f, 0.0f, 1.0f);	// ǰ��
		vertexDataArr[i + 16].tangent = XMFLOAT4(-1.0f, 0.0f, 0.0f, 1.0f);
		vertexDataArr[i + 16].color = color;

		vertexDataArr[i + 20].normal = XMFLOAT3(0.0f, 0.0f, -1.0f); // ����
		vertexDataArr[i + 20].tangent = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
		vertexDataArr[i + 20].color = color;
	}

	for (int i = 0; i < 6; ++i)
	{
		vertexDataArr[i * 4].tex = XMFLOAT2(0.0f, 1.0f);
		vertexDataArr[i * 4 + 1].tex = XMFLOAT2(0.0f, 0.0f);
		vertexDataArr[i * 4 + 2].tex = XMFLOAT2(1.0f, 0.0f);
		vertexDataArr[i * 4 + 3].tex = XMFLOAT2(1.0f, 1.0f);
	}

	for (int i = 0; i < 24; ++i)
	{
		InsertVertexElement(meshData.vertexVec[i], vertexDataArr[i]);
	}

	meshData.indexVec = {
		0, 1, 2, 2, 3, 0,		// ����
		4, 5, 6, 6, 7, 4,		// ����
		8, 9, 10, 10, 11, 8,	// ����
		12, 13, 14, 14, 15, 12,	// ����
		16, 17, 18, 18, 19, 16, // ����
		20, 21, 22, 22, 23, 20	// ����
	};

	return meshData;
}

template<class VertexType, class IndexType>
inline Geometry::MeshData<VertexType, IndexType> Geometry::CreateCylinder(float radius, float height, int slices, const DirectX::XMFLOAT4 & color)
{
	using namespace DirectX;

	auto meshData = CreateCylinderNoCap<VertexType, IndexType>(radius, height, slices, color);
	meshData.vertexVec.resize(4 * (slices + 1) + 2);
	meshData.indexVec.resize(12 * slices);

	float h2 = height / 2;
	float theta = 0.0f;
	float per_theta = XM_2PI / slices;

	IndexType vIndex = 2 * (slices + 1), iIndex = 6 * slices;
	IndexType offset = 2 * (slices + 1);
	VertexData vertexData;

	// ���붥��Բ��
	vertexData = { XMFLOAT3(0.0f, h2, 0.0f), XMFLOAT3(0.0f, 1.0f, 0.0f),
		XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), color, XMFLOAT2(0.5f, 0.5f) };
	InsertVertexElement(meshData.vertexVec[vIndex++], vertexData);

	// ���붥��Բ�ϸ���
	for (int i = 0; i <= slices; ++i)
	{
		theta = i * per_theta;
		vertexData = { XMFLOAT3(radius * cosf(theta), h2, radius * sinf(theta)), XMFLOAT3(0.0f, 1.0f, 0.0f),
			XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), color, XMFLOAT2(cosf(theta) / 2 + 0.5f, sinf(theta) / 2 + 0.5f) };
		InsertVertexElement(meshData.vertexVec[vIndex++], vertexData);
	}

	// ����ײ�Բ�ϸ���
	for (int i = 0; i <= slices; ++i)
	{
		theta = i * per_theta;
		vertexData = { XMFLOAT3(radius * cosf(theta), -h2, radius * sinf(theta)), XMFLOAT3(0.0f, -1.0f, 0.0f),
			XMFLOAT4(-1.0f, 0.0f, 0.0f, 1.0f), color, XMFLOAT2(cosf(theta) / 2 + 0.5f, sinf(theta) / 2 + 0.5f) };
		InsertVertexElement(meshData.vertexVec[vIndex++], vertexData);
	}

	// ����׶�Բ��
	vertexData = { XMFLOAT3(0.0f, -h2, 0.0f), XMFLOAT3(0.0f, -1.0f, 0.0f),
		XMFLOAT4(-1.0f, 0.0f, 0.0f, 1.0f), color, XMFLOAT2(0.5f, 0.5f) };
	InsertVertexElement(meshData.vertexVec[vIndex++], vertexData);

	// �𽥷��붥������������
	for (int i = 1; i <= slices; ++i)
	{
		meshData.indexVec[iIndex++] = offset;
		meshData.indexVec[iIndex++] = offset + i % (slices + 1) + 1;
		meshData.indexVec[iIndex++] = offset + i;
	}

	// �𽥷���ײ�����������
	offset += slices + 2;
	for (int i = 1; i <= slices; ++i)
	{
		meshData.indexVec[iIndex++] = offset;
		meshData.indexVec[iIndex++] = offset + i;
		meshData.indexVec[iIndex++] = offset + i % (slices + 1) + 1;
	}

	return meshData;
}

template<class VertexType, class IndexType>
inline Geometry::MeshData<VertexType, IndexType> Geometry::CreateCylinderNoCap(float radius, float height, int slices, const DirectX::XMFLOAT4 & color)
{
	using namespace DirectX;

	MeshData<VertexType, IndexType> meshData;
	meshData.vertexVec.resize(2 * (slices + 1));
	meshData.indexVec.resize(6 * slices);

	size_t iIndex = 0;

	float h2 = height / 2;
	float theta = 0.0f;
	float per_theta = XM_2PI / slices;

	VertexData vertexData;

	// ������涥�˵�
	for (int i = 0; i <= slices; ++i)
	{
		theta = i * per_theta;
		vertexData = { XMFLOAT3(radius * cosf(theta), h2, radius * sinf(theta)), XMFLOAT3(cosf(theta), 0.0f, sinf(theta)),
			XMFLOAT4(-sinf(theta), 0.0f, cosf(theta), 1.0f), color, XMFLOAT2(theta / XM_2PI, 0.0f) };
		InsertVertexElement(meshData.vertexVec[i], vertexData);
	}

	// �������׶˵�
	for (int i = 0; i <= slices; ++i)
	{
		theta = i * per_theta;
		vertexData = { XMFLOAT3(radius * cosf(theta), -h2, radius * sinf(theta)), XMFLOAT3(cosf(theta), 0.0f, sinf(theta)),
			XMFLOAT4(-sinf(theta), 0.0f, cosf(theta), 1.0f), color, XMFLOAT2(theta / XM_2PI, 1.0f) };
		InsertVertexElement(meshData.vertexVec[(slices + 1) + i], vertexData);
	}

	// ��������
	for (int i = 0; i < slices; ++i)
	{
		meshData.indexVec[iIndex++] = i;
		meshData.indexVec[iIndex++] = i + 1;
		meshData.indexVec[iIndex++] = (slices + 1) + i + 1;

		meshData.indexVec[iIndex++] = (slices + 1) + i + 1;
		meshData.indexVec[iIndex++] = (slices + 1) + i;
		meshData.indexVec[iIndex++] = i;
	}


	return meshData;
}

template<class VertexType, class IndexType>
inline Geometry::MeshData<VertexType, IndexType> Geometry::Create2DShow(const DirectX::XMFLOAT2 & center, const DirectX::XMFLOAT2 & scale,
	const DirectX::XMFLOAT4 & color)
{
	return Create2DShow<VertexType, IndexType>(center.x, center.y, scale.x, scale.y, color);
}

template<class VertexType, class IndexType>
inline Geometry::MeshData<VertexType, IndexType> Geometry::Create2DShow(float centerX, float centerY, float scaleX, float scaleY, const DirectX::XMFLOAT4 & color)
{
	using namespace DirectX;

	MeshData<VertexType, IndexType> meshData;
	meshData.vertexVec.resize(4);

	VertexData vertexData;
	IndexType vIndex = 0;

	vertexData = { XMFLOAT3(centerX - scaleX, centerY - scaleY, 0.0f), XMFLOAT3(0.0f, 0.0f, -1.0f),
		XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), color, XMFLOAT2(0.0f, 1.0f) };
	InsertVertexElement(meshData.vertexVec[vIndex++], vertexData);

	vertexData = { XMFLOAT3(centerX - scaleX, centerY + scaleY, 0.0f), XMFLOAT3(0.0f, 0.0f, -1.0f),
		XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), color, XMFLOAT2(0.0f, 0.0f) };
	InsertVertexElement(meshData.vertexVec[vIndex++], vertexData);

	vertexData = { XMFLOAT3(centerX + scaleX, centerY + scaleY, 0.0f), XMFLOAT3(0.0f, 0.0f, -1.0f),
		XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), color, XMFLOAT2(1.0f, 0.0f) };
	InsertVertexElement(meshData.vertexVec[vIndex++], vertexData);

	vertexData = { XMFLOAT3(centerX + scaleX, centerY - scaleY, 0.0f), XMFLOAT3(0.0f, 0.0f, -1.0f),
		XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), color, XMFLOAT2(1.0f, 1.0f) };
	InsertVertexElement(meshData.vertexVec[vIndex++], vertexData);

	meshData.indexVec = { 0, 1, 2, 2, 3, 0 };
	return meshData;
}

template<class VertexType, class IndexType>
inline Geometry::MeshData<VertexType, IndexType> Geometry::CreatePlane(const DirectX::XMFLOAT3 & center, const DirectX::XMFLOAT2 & planeSize,
	const DirectX::XMFLOAT2 & maxTexCoord, const DirectX::XMFLOAT4 & color)
{
	return CreatePlane<VertexType, IndexType>(center.x, center.y, center.z, planeSize.x, planeSize.y, maxTexCoord.x, maxTexCoord.y, color);
}

template<class VertexType, class IndexType>
inline Geometry::MeshData<VertexType, IndexType> Geometry::CreatePlane(float centerX, float centerY, float centerZ, float width, float depth, float texU, float texV, const DirectX::XMFLOAT4 & color)
{
	using namespace DirectX;

	MeshData<VertexType, IndexType> meshData;
	meshData.vertexVec.resize(4);

	VertexData vertexData;
	IndexType vIndex = 0;

	vertexData = { XMFLOAT3(centerX - width / 2, centerY, centerZ - depth / 2), XMFLOAT3(0.0f, 1.0f, 0.0f),
		XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), color, XMFLOAT2(0.0f, texV) };
	InsertVertexElement(meshData.vertexVec[vIndex++], vertexData);

	vertexData = { XMFLOAT3(centerX - width / 2, centerY, centerZ + depth / 2), XMFLOAT3(0.0f, 1.0f, 0.0f),
		XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), color, XMFLOAT2(0.0f, 0.0f) };
	InsertVertexElement(meshData.vertexVec[vIndex++], vertexData);

	vertexData = { XMFLOAT3(centerX + width / 2, centerY, centerZ + depth / 2), XMFLOAT3(0.0f, 1.0f, 0.0f),
		XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), color, XMFLOAT2(texU, 0.0f) };
	InsertVertexElement(meshData.vertexVec[vIndex++], vertexData);

	vertexData = { XMFLOAT3(centerX + width / 2, centerY, centerZ - depth / 2), XMFLOAT3(0.0f, 1.0f, 0.0f),
		XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), color, XMFLOAT2(texU, texV) };
	InsertVertexElement(meshData.vertexVec[vIndex++], vertexData);

	meshData.indexVec = { 0, 1, 2, 2, 3, 0 };
	return meshData;
}

#endif

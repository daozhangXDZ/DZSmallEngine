#pragma once
#include <d3d11.h>
#include <DirectXMath.h>

//struct BaseVertexDesc
//{
//public:
//	BaseVertexDesc() {}
//	BaseVertexDesc(float x, float y, float z)
//		:pos(x, y, z) {}
//public:
//	DirectX::XMFLOAT3 pos;
//
//};

struct VertexPos
{
public:
	VertexPos() {};
	VertexPos(float x, float y, float z) :pos(x, y, z) {}
public:
	DirectX::XMFLOAT3 pos;
	static const D3D11_INPUT_ELEMENT_DESC inputLayout[1];
};

struct VertexPosColor
{
public:
	VertexPosColor() {};
	VertexPosColor(float x, float y, float z) :pos(x, y, z) {}
public:
	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT4 color;
	static const D3D11_INPUT_ELEMENT_DESC inputLayout[2];
};

struct VertexPosTex
{
public:
	VertexPosTex() {};
	VertexPosTex(float x, float y, float z) :pos(x, y, z) {}
public:
	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT2 tex;
	static const D3D11_INPUT_ELEMENT_DESC inputLayout[2];
};

struct VertexPosSize
{
public:
	VertexPosSize() {};
	VertexPosSize(float x, float y, float z) :pos(x, y, z) {}
public:
	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT2 size;
	static const D3D11_INPUT_ELEMENT_DESC inputLayout[2];
};

struct VertexPosNormalColor
{
public:
	VertexPosNormalColor() {};
	VertexPosNormalColor(float x, float y, float z) :pos(x, y, z) {}
public:
	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT3 normal;
	DirectX::XMFLOAT4 color;
	static const D3D11_INPUT_ELEMENT_DESC inputLayout[3];
};


struct VertexPosNormalTex
{
public:
	VertexPosNormalTex(float x, float y, float z) :pos(x, y, z) {}
	VertexPosNormalTex() :VertexPosNormalTex(1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0) {}
	VertexPosNormalTex(float x, float y, float z, float nx, float ny, float nz, float u, float v)
		:pos(x, y, z), normal(nx, ny, nz), tex(u, v)
	{

	}
public:
	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT3 normal;
	DirectX::XMFLOAT2 tex;
	
	static const D3D11_INPUT_ELEMENT_DESC inputLayout[3];
};

struct VertexPosNormalTangentTex
{
public:

	VertexPosNormalTangentTex() {};
	VertexPosNormalTangentTex(float x, float y, float z) :pos(x, y, z) {}
public:
	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT3 normal;
	DirectX::XMFLOAT4 tangent;
	DirectX::XMFLOAT2 tex;
	static const D3D11_INPUT_ELEMENT_DESC inputLayout[4];
};
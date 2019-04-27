#pragma once
#include <DirectXMath.h>
using namespace DirectX;
struct ViewPortDesc
{
public:
	XMMATRIX viewMat;
	XMMATRIX ProjMat;
	XMFLOAT3 eyepos;
	XMFLOAT2 Near_Far;
};

struct RenderViewBoard
{
public:
	float ViewWidth;
	float ViewHeight;
};
#pragma once
#include <DirectXMath.h>
struct ViewPortDesc
{
public:
	XMMATRIX viewMat;
	XMMATRIX ProjMat;
	XMFLOAT3 eyepos;
};

struct RenderViewBoard
{
public:
	float ViewWidth;
	float ViewHeight;
};
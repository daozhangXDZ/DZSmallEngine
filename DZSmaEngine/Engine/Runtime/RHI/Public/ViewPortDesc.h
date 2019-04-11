#pragma once
#include <DirectXMath.h>
struct ViewPortDesc
{
public:
	XMMATRIX viewMat;
	XMMATRIX ProjMat;
};

struct RenderViewBoard
{
public:
	float ViewWidth;
	float ViewHeight;
};
#pragma once
#include "CoreMinimal.h"
struct MaterialOutPut
{
	DirectX::XMFLOAT4 Ambient;
	DirectX::XMFLOAT4 Diffuse;
	DirectX::XMFLOAT4 Specular; // w = 镜面反射强度
	DirectX::XMFLOAT4 Reflect;
	bool isUseDiffTexture;
	bool isUseNormalTexture;
};
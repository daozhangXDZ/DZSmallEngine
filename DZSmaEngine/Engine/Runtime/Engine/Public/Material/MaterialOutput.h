#pragma once
#include "CoreMinimal.h"
struct MaterialOutPut
{
	DirectX::XMFLOAT4 Ambient;
	DirectX::XMFLOAT4 Diffuse;
	DirectX::XMFLOAT4 Specular; // w = ���淴��ǿ��
	DirectX::XMFLOAT4 Reflect;
	bool isUseDiffTexture;
	bool isUseNormalTexture;
};
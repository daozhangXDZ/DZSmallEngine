#pragma once
#include <cstring>
#include <DirectXMath.h>

enum ESceneLightType
{
	DirectionLight = 0,
	PointLight = 1,
	SpotLight = 2,
};

/**
 * Scene Info Light to Render
 */
struct FSceneLightInfo
{
	FSceneLightInfo() { memset(this, 0, sizeof(FSceneLightInfo)); }

	ESceneLightType Etype = ESceneLightType::DirectionLight;
	DirectX::XMFLOAT4 Ambient;
	DirectX::XMFLOAT4 Diffuse;
	DirectX::XMFLOAT4 Specular;

	DirectX::XMFLOAT3 Direction;
	DirectX::XMFLOAT3 Position;
	float Range;
	float Spot;
	DirectX::XMMATRIX view;
	DirectX::XMMATRIX proj;
	DirectX::XMFLOAT3 Att;
};
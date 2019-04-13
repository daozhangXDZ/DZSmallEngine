#pragma once
#include <cstring>
#include <DirectXMath.h>


// 各种类型灯光允许的最大数目
class CEffect
{
public:
	// 各种类型灯光允许的最大数目
	static const int maxLights = 1;
};
struct DirectionalLight
{
	DirectionalLight() { memset(this, 0, sizeof(DirectionalLight)); }

	DirectX::XMFLOAT4 Ambient;
	DirectX::XMFLOAT4 Diffuse;
	DirectX::XMFLOAT4 Specular;
	DirectX::XMFLOAT3 Direction;
	float Pad; // 最后用一个浮点数填充使得该结构体大小满足16的倍数，便于我们以后在HLSL设置数组
};

// 点光
struct PointLight
{
	PointLight() { memset(this, 0, sizeof(PointLight)); }

	DirectX::XMFLOAT4 Ambient;
	DirectX::XMFLOAT4 Diffuse;
	DirectX::XMFLOAT4 Specular;

	// 打包成4D向量: (Position, Range)
	DirectX::XMFLOAT3 Position;
	float Range;

	// 打包成4D向量: (A0, A1, A2, Pad)
	DirectX::XMFLOAT3 Att;
	float Pad; // 最后用一个浮点数填充使得该结构体大小满足16的倍数，便于我们以后在HLSL设置数组
};

// 聚光灯
struct SpotLight
{
	SpotLight() { memset(this, 0, sizeof(SpotLight)); }

	DirectX::XMFLOAT4 Ambient;
	DirectX::XMFLOAT4 Diffuse;
	DirectX::XMFLOAT4 Specular;

	// 打包成4D向量: (Position, Range)
	DirectX::XMFLOAT3 Position;
	float Range;

	// 打包成4D向量: (Direction, Spot)
	DirectX::XMFLOAT3 Direction;
	float Spot;

	// 打包成4D向量: (Att, Pad)
	DirectX::XMFLOAT3 Att;
	float Pad; // 最后用一个浮点数填充使得该结构体大小满足16的倍数，便于我们以后在HLSL设置数组
};

// 物体表面材质
struct Material
{
	Material() { memset(this, 0, sizeof(Material)); }

	DirectX::XMFLOAT4 Ambient;
	DirectX::XMFLOAT4 Diffuse;
	DirectX::XMFLOAT4 Specular; // w = 镜面反射强度
	DirectX::XMFLOAT4 Reflect;
};

struct CBChangesEveryDrawing
{
	//DirectX::XMMATRIX WorldToView;
	DirectX::XMMATRIX world;
	DirectX::XMMATRIX worldInvTranspose;
	Material material;
};

struct CBDrawingStates
{
	int isReflection;
	int isShadow;
	DirectX::XMFLOAT3 pad;
};

struct CBChangesEveryFrame
{
	DirectX::XMMATRIX view;
	DirectX::XMVECTOR eyePos;

};

struct CBChangesOnResize
{
	DirectX::XMMATRIX proj;
};


struct CBChangesRarely
{
	DirectX::XMMATRIX reflection;
	DirectX::XMMATRIX shadow;
	DirectX::XMMATRIX refShadow;
	DirectionalLight dirLight[CEffect::maxLights];
	PointLight pointLight[CEffect::maxLights];
	SpotLight spotLight[CEffect::maxLights];
};
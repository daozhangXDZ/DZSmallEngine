#pragma once
#include <cstring>
#include <DirectXMath.h>


// 各种类型灯光允许的最大数目
class CEffect
{
public:
	// 各种类型灯光允许的最大数目
	static const int maxDireLights = 5;
	static const int maxPointLights = 5;
	static const int maxSpotLights = 5;
};

struct ShaderDirectionalLight
{
	ShaderDirectionalLight() { memset(this, 0, sizeof(ShaderDirectionalLight)); }

	DirectX::XMFLOAT4 Ambient;
	DirectX::XMFLOAT4 Diffuse;
	DirectX::XMFLOAT4 Specular;

	DirectX::XMFLOAT3 Direction;
	float Pad; 

	DirectX::XMMATRIX view;
	DirectX::XMMATRIX proj;

	DirectX::XMFLOAT3 Att;
	float Pad2; // 最后用一个浮点数填充使得该结构体大小满足16的倍数，便于我们以后在HLSL设置数组
};

// 点光
struct ShaderPointLight
{
	ShaderPointLight() { memset(this, 0, sizeof(ShaderPointLight)); }

	DirectX::XMFLOAT4 Ambient;
	DirectX::XMFLOAT4 Diffuse;
	DirectX::XMFLOAT4 Specular;

	// 打包成4D向量: (Position, Range)
	DirectX::XMFLOAT3 Position;
	float Range;

	DirectX::XMMATRIX view;
	DirectX::XMMATRIX proj;
	// 打包成4D向量: (A0, A1, A2, Pad)
	DirectX::XMFLOAT3 Att;
	float Pad; // 最后用一个浮点数填充使得该结构体大小满足16的倍数，便于我们以后在HLSL设置数组
};

// 聚光灯
struct ShaderSpotLight
{
	ShaderSpotLight() { memset(this, 0, sizeof(ShaderSpotLight)); }

	DirectX::XMFLOAT4 Ambient;
	DirectX::XMFLOAT4 Diffuse;
	DirectX::XMFLOAT4 Specular;

	// 打包成4D向量: (Position, Range)
	DirectX::XMFLOAT3 Position;
	float Range;

	// 打包成4D向量: (Direction, Spot)
	DirectX::XMFLOAT3 Direction;
	float Spot;

	DirectX::XMMATRIX view;
	DirectX::XMMATRIX proj;

	// 打包成4D向量: (Att, Pad)
	DirectX::XMFLOAT3 Att;
	float Pad; // 最后用一个浮点数填充使得该结构体大小满足16的倍数，便于我们以后在HLSL设置数组
};

// 物体表面材质
struct ShaderMaterial
{
	ShaderMaterial() { memset(this, 0, sizeof(ShaderMaterial)); }
	int materialType;
	// 是否使用Diff
	int diffTextureUsed;
	// 是否使用normal纹理
	int normalTextureUsed;
	// 
	int padX;
	DirectX::XMFLOAT4 Ambient;
	DirectX::XMFLOAT4 Diffuse;
	DirectX::XMFLOAT4 Specular; // w = 镜面反射强度
	DirectX::XMFLOAT4 Reflect;
	float Pad;
};

struct CBChangesEveryDrawing
{
	DirectX::XMMATRIX world;
	DirectX::XMMATRIX worldInvTranspose;
	ShaderMaterial material;
};

struct CBDrawingStates
{
	// 是否反射
	int reflectionEnabled;
	// 是否折射
	int refractionEnabled;
	// 是否阴影
	int isShadowed;
	// 折射率
	float eta;	
};

struct CBChangesEveryFrame
{
	DirectX::XMMATRIX view;
	DirectX::XMVECTOR eyePos;

};

struct CBChangesOnResize
{
	DirectX::XMMATRIX proj;
	DirectX::XMFLOAT2 Clip_N_F;
	float Pad;
};


struct CBChangesRarely
{
	DirectX::XMMATRIX reflection;
	DirectX::XMMATRIX shadow;
	DirectX::XMMATRIX refShadow;
	ShaderDirectionalLight dirLight[CEffect::maxDireLights];
	ShaderPointLight pointLight[CEffect::maxPointLights];
	ShaderSpotLight spotLight[CEffect::maxSpotLights];

	int DirLightCount;
	int pointLightCount;
	int spotLighttCount;
	float PadCBChangesRarely;
};
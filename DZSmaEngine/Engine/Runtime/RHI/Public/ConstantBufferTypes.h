#pragma once
#include <cstring>
#include <DirectXMath.h>


// �������͵ƹ�����������Ŀ
class CEffect
{
public:
	// �������͵ƹ�����������Ŀ
	static const int maxLights = 1;
};
struct DirectionalLight
{
	DirectionalLight() { memset(this, 0, sizeof(DirectionalLight)); }

	DirectX::XMFLOAT4 Ambient;
	DirectX::XMFLOAT4 Diffuse;
	DirectX::XMFLOAT4 Specular;
	DirectX::XMFLOAT3 Direction;
	float Pad; // �����һ�����������ʹ�øýṹ���С����16�ı��������������Ժ���HLSL��������
};

// ���
struct PointLight
{
	PointLight() { memset(this, 0, sizeof(PointLight)); }

	DirectX::XMFLOAT4 Ambient;
	DirectX::XMFLOAT4 Diffuse;
	DirectX::XMFLOAT4 Specular;

	// �����4D����: (Position, Range)
	DirectX::XMFLOAT3 Position;
	float Range;

	// �����4D����: (A0, A1, A2, Pad)
	DirectX::XMFLOAT3 Att;
	float Pad; // �����һ�����������ʹ�øýṹ���С����16�ı��������������Ժ���HLSL��������
};

// �۹��
struct SpotLight
{
	SpotLight() { memset(this, 0, sizeof(SpotLight)); }

	DirectX::XMFLOAT4 Ambient;
	DirectX::XMFLOAT4 Diffuse;
	DirectX::XMFLOAT4 Specular;

	// �����4D����: (Position, Range)
	DirectX::XMFLOAT3 Position;
	float Range;

	// �����4D����: (Direction, Spot)
	DirectX::XMFLOAT3 Direction;
	float Spot;

	// �����4D����: (Att, Pad)
	DirectX::XMFLOAT3 Att;
	float Pad; // �����һ�����������ʹ�øýṹ���С����16�ı��������������Ժ���HLSL��������
};

// ����������
struct Material
{
	Material() { memset(this, 0, sizeof(Material)); }

	DirectX::XMFLOAT4 Ambient;
	DirectX::XMFLOAT4 Diffuse;
	DirectX::XMFLOAT4 Specular; // w = ���淴��ǿ��
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
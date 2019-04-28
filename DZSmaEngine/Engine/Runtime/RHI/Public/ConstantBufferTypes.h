#pragma once
#include <cstring>
#include <DirectXMath.h>


// �������͵ƹ�����������Ŀ
class CEffect
{
public:
	// �������͵ƹ�����������Ŀ
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
	float Pad2; // �����һ�����������ʹ�øýṹ���С����16�ı��������������Ժ���HLSL��������
};

// ���
struct ShaderPointLight
{
	ShaderPointLight() { memset(this, 0, sizeof(ShaderPointLight)); }

	DirectX::XMFLOAT4 Ambient;
	DirectX::XMFLOAT4 Diffuse;
	DirectX::XMFLOAT4 Specular;

	// �����4D����: (Position, Range)
	DirectX::XMFLOAT3 Position;
	float Range;

	DirectX::XMMATRIX view;
	DirectX::XMMATRIX proj;
	// �����4D����: (A0, A1, A2, Pad)
	DirectX::XMFLOAT3 Att;
	float Pad; // �����һ�����������ʹ�øýṹ���С����16�ı��������������Ժ���HLSL��������
};

// �۹��
struct ShaderSpotLight
{
	ShaderSpotLight() { memset(this, 0, sizeof(ShaderSpotLight)); }

	DirectX::XMFLOAT4 Ambient;
	DirectX::XMFLOAT4 Diffuse;
	DirectX::XMFLOAT4 Specular;

	// �����4D����: (Position, Range)
	DirectX::XMFLOAT3 Position;
	float Range;

	// �����4D����: (Direction, Spot)
	DirectX::XMFLOAT3 Direction;
	float Spot;

	DirectX::XMMATRIX view;
	DirectX::XMMATRIX proj;

	// �����4D����: (Att, Pad)
	DirectX::XMFLOAT3 Att;
	float Pad; // �����һ�����������ʹ�øýṹ���С����16�ı��������������Ժ���HLSL��������
};

// ����������
struct ShaderMaterial
{
	ShaderMaterial() { memset(this, 0, sizeof(ShaderMaterial)); }
	int materialType;
	// �Ƿ�ʹ��Diff
	int diffTextureUsed;
	// �Ƿ�ʹ��normal����
	int normalTextureUsed;
	// 
	int padX;
	DirectX::XMFLOAT4 Ambient;
	DirectX::XMFLOAT4 Diffuse;
	DirectX::XMFLOAT4 Specular; // w = ���淴��ǿ��
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
	// �Ƿ���
	int reflectionEnabled;
	// �Ƿ�����
	int refractionEnabled;
	// �Ƿ���Ӱ
	int isShadowed;
	// ������
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
#pragma once
#include "Material.h"
#include "ConstantBufferTypes.h"
class MaterialUtil
{
public:
	static void fillShaderMaterial(BaseMaterial* material, ShaderMaterial* shaderOut);

	static BaseMaterial* CreateOneMateria(
		MaterialType materialType,
		std::wstring pVSName, std::wstring pPSName,
		XMFLOAT4 Ambient, XMFLOAT4 Diffcuse, XMFLOAT4 Specular, XMFLOAT4 reflection);

	static BaseMaterial* CreateOneMateria(MaterialType materialType, XMFLOAT4 Ambient, XMFLOAT4 Diffcuse, XMFLOAT4 Specular, XMFLOAT4 reflection);

	static BaseMaterial* CreateOneMateria(
		MaterialType materialType,
		std::wstring pMainTextureFilePath, std::wstring pNormalTextureFilePath,
		std::wstring pVSName, std::wstring pPSName,
		XMFLOAT4 Ambient, XMFLOAT4 Diffcuse, XMFLOAT4 Specular, XMFLOAT4 reflection);
};
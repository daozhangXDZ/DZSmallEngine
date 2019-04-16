#include "Material/MaterialUtils.h"
#include "ShaderUtils.h"

void MaterialUtil::fillShaderMaterial(BaseMaterial* material, ShaderMaterial* shaderOut)
{
	material->FillShader(shaderOut);
}
BaseMaterial * MaterialUtil::CreateOneMateria(MaterialType materialType, std::wstring pVSName, std::wstring pPSName, XMFLOAT4 Ambient, XMFLOAT4 Diffcuse, XMFLOAT4 Specular, XMFLOAT4 reflection)
{
	return CreateOneMateria(materialType,L"",L"",pVSName,pPSName,Ambient,Diffcuse,Specular,reflection);
}
BaseMaterial * MaterialUtil::CreateOneMateria(MaterialType materialType, XMFLOAT4 Ambient, XMFLOAT4 Diffcuse, XMFLOAT4 Specular, XMFLOAT4 reflection)
{
	return CreateOneMateria(materialType, L"", L"", L"", L"", Ambient, Diffcuse, Specular, reflection);
}
BaseMaterial * MaterialUtil::CreateOneMateria(MaterialType materialType, std::wstring pMainTextureFilePath, std::wstring pNormalTextureFilePath, std::wstring pVSName, std::wstring pPSName, XMFLOAT4 Ambient, XMFLOAT4 Diffcuse, XMFLOAT4 Specular, XMFLOAT4 reflection)
{
	BaseMaterial* vOutMaterial = new BaseMaterial();
	vOutMaterial->AmbientNode->fill(Ambient);
	vOutMaterial->DiffuseNode->fill(Diffcuse);
	vOutMaterial->SpecularNode->fill(Specular);
	vOutMaterial->ReflectNode->fill(reflection);
	vOutMaterial->materialType = materialType;
	if (pVSName != L"")
	{
		vOutMaterial->mVertexShader = ShaderUtils::GetShaderResource(pVSName)->getVertexShader();
		vOutMaterial->mInputElement = RHICreateRHIInputElement(VertexPosNormalTangentTex::inputLayout
			, ARRAYSIZE(VertexPosNormalTangentTex::inputLayout));
		vOutMaterial->mInputLayout = RHICreateInputLayout(vOutMaterial->mInputElement, vOutMaterial->mVertexShader);
	}
	if (pPSName != L"")
	{
		vOutMaterial->mPixelShader = ShaderUtils::GetShaderResource(pPSName)->getPixelShader();

	}
	if (pMainTextureFilePath != L"")
	{
		vOutMaterial->mMainTexture = RHICreateShaderResourcesView(pMainTextureFilePath);
	}
	if (pNormalTextureFilePath != L"")
	{
		vOutMaterial->mNormalTexture = RHICreateShaderResourcesView(pNormalTextureFilePath);
	}
	return vOutMaterial;
}
;
#include "Shader.h"

#ifdef _DEBUG //Debug Mode
#ifdef _WIN64 //x64
std::wstring  shaderfolder = L"..\\x64\\Debug\\Shaders\\";
#else  //x86 (Win32)
std::wstring  shaderfolder = L"..\\Debug\\Shaders\\";
#endif
#else //Release Mode
#ifdef _WIN64 //x64
std::wstring  shaderfolder = L"..\\x64\\Release\\Shaders\\";
#else  //x86 (Win32)
std::wstring  shaderfolder = L"..\\Release\\Shaders\\";
#endif
#endif

std::map<std::wstring, int> ShaderResource::ShaderResourceIdMap;
std::vector<ShaderResource*> ShaderResource::ShaderList;

RenderResource::RenderResource()
{
}

RenderResource::RenderResource(std::wstring pFileName)
	:mFileName(pFileName)
{

}


ShaderResource::ShaderResource()
{

}

ShaderResource::ShaderResource(FShaderCompilerOutput* outPut) :
	RenderResource(outPut->FileName)
	,mTarget(outPut->mTarget)
{
	ShaderResourceIdMap.insert(std::pair<std::wstring, int>(mFileName, ShaderList.size()));
	ShaderList.push_back(this);
}

ShaderResource * ShaderResource::GetShaderResourceByName(std::wstring pShaderName)
{
	auto  ite = ShaderResourceIdMap.find(pShaderName);
	if (ite != ShaderResourceIdMap.end())
	{
		int vIndexList = ite->second;
		if (vIndexList < ShaderList.size())
		{
			return ShaderList[vIndexList];
		}
	}
	return nullptr;
}

bool ShaderResource::InitRHI()
{
	switch (mTarget.Frequency)
	{
	case EShaderFrequency::SF_Vertex:
	{
		vertexShader = RHICreateVertexShader(shaderfolder + mFileName);
		break;
	}

	case EShaderFrequency::SF_Pixel:
	{
		pixelShader = RHICreatePixelShader(shaderfolder + mFileName);
		break;
	}
	default:
		break;
	}
	return true;
}


RHIPixelShaderRef ShaderResource::getPixelShader()
{
	return pixelShader;
}

RHIVertexShaderRef ShaderResource::getVertexShader()
{
	return vertexShader;
}

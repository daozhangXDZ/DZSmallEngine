#pragma once
#include "RHIDefine.h"
struct FShaderTarget
{
	//��ɫĿ�꣨Ƭ�Σ�����Vertex, Geom, Dom, Hull, Pixel, Computer
	uint32 Frequency;
};

/** The output of the shader compiler. */
struct FShaderCompilerOutput
{
	std::wstring FileName;
	FShaderTarget mTarget;
};
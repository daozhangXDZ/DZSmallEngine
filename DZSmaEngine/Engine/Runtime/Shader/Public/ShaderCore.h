#pragma once
#include "RHIDefine.h"
struct FShaderTarget
{
	//着色目标（片段）：如Vertex, Geom, Dom, Hull, Pixel, Computer
	uint32 Frequency;
};

/** The output of the shader compiler. */
struct FShaderCompilerOutput
{
	std::wstring FileName;
	FShaderTarget mTarget;
};
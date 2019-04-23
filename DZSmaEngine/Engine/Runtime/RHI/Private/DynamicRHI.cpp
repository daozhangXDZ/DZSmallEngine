#pragma once
#include "DynamicRHI.h"
#include "EngineGlobal.h"
#include "ShaderUtils.h"
#include "D3D11/D3D11DynamicRHI.h"

DynamicRHI* GDynamicRHI = nullptr;
// Globals.
void RHIInit()
{
	//ÁãÊ³
	if (1)
	{
		GDynamicRHI = new D3D11DynamicRHI();
	}
	else if (2)
	{
		GDynamicRHI = nullptr;
	}
	GDynamicRHI->InitRender();
}

void RHITick()
{
	GDynamicRHI->Tick();
}

void RHIExit()
{
	GDynamicRHI->Exit();
}

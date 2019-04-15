#pragma once
#include "DynamicRHI.h"
#include "EngineGlobal.h"
#include "ShaderUtils.h"
// Globals.
void RHIInit()
{
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



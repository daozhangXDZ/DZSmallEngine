#pragma once
#include "DynamicRHI.h"
#include "EngineGlobal.h"
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



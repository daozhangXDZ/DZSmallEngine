#pragma once
#include "BaseEngine.h"
#include "Windows.h"
#include "EngineApplication.h"
#include "DynamicRHI.h"
#include "WindowsPlatform/GameTimer.h"

extern BaseEngine* GEngine;
extern HINSTANCE* currAppIns;
extern EngineApplication* GEngineApliation;
extern DynamicRHI* GDynamicRHI;
extern GameTimer*  GWorldTime;
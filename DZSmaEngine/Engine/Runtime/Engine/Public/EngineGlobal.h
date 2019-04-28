#pragma once
#include "BaseEngine.h"
#include "Windows.h"
#include "EngineApplication.h"
#include "DynamicRHI.h"
#include "WindowsPlatform/GameTimer.h"

extern BaseEngine* GEngine;
extern HINSTANCE* currAppIns;
extern DynamicRHI* GDynamicRHI;
extern GameTimer*  GWorldTime;

const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = false;
const float SCREEN_DEPTH = 100.0f;
const float SCREEN_NEAR = 1.0f;
const int SHADOWMAP_WIDTH = 1024;
const int SHADOWMAP_HEIGHT = 1024;
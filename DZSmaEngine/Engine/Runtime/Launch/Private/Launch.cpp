#include "CoreMinimal.h"
#include "LaunchEngineLoop.h"
#include <Windows.h>
#include "EngineGlobal.h"

FEngineLoop	GEngineLoop;
HINSTANCE* currAppIns = nullptr;

/**
 * PreInits the engine loop
 */
int EnginePreInit()
{
	int ErrorLevel = GEngineLoop.PreInit();

	return(ErrorLevel);
}


int EngineInit()
{
	int ErrorLevel = GEngineLoop.Init();

	return(ErrorLevel);
}


int EngineTick(void)
{
	return GEngineLoop.Tick();
}


void EngineExit(void)
{
	GEngineLoop.Exit();
}


int GuardedMain(HINSTANCE hInstance)
{
	currAppIns = &hInstance;
	struct EngineLoopCleanupGuard
	{
		~EngineLoopCleanupGuard()
		{
			EngineExit();
		}
	} CleanupGuard;

	int ErrorLevel = EnginePreInit();

	// exit if PreInit failed.
	if (ErrorLevel != 0)
	{
		return ErrorLevel;
	}

	ErrorLevel = EngineInit();
	while (EngineTick() == 1)
	{
		continue;
	}
	EngineExit();
	return ErrorLevel;
}
#include "EngineApplication.h"
#include "LaunchEngineLoop.h"
#include "EngineGlobal.h"
#include "GameEngine.h"
#include "RHI.h"
#include "ShaderUtils.h"
#include "MoviePlayer.h"

BaseEngine* GEngine = nullptr;
GameTimer*	GWorldTime = nullptr;






FEngineLoop::FEngineLoop()
{


}

int FEngineLoop::PreInit()
{
	GEngine = new GameEngine();
	EngineApplication::get()->Start();
	CreateMoviePlayer();
	RHIInit();
	return 0;
}



int FEngineLoop::Init()
{
	GetMoviePlayer()->Initialize();
	{
		ShaderUtils::InitCombileAllShader();
		GEngine->Init();
		{
			GWorldTime = new GameTimer();
			GWorldTime->Reset();
			GWorldTime->Start();
		}
	}
	return 0;
}


int FEngineLoop::Exit()
{
	GEngine->Exit();
	RHIExit();
	if (GWorldTime != nullptr)
	{
		GWorldTime->Stop();
	}
	return 0;
}

int FEngineLoop::Tick()
{
	GWorldTime->Tick();
	RHITick();
	EngineApplication::get()->Tick(GWorldTime->DeltaTime());
	GEngine->Tick(GWorldTime->DeltaTime());
	if (!GetMoviePlayer()->WaitForMovieToFinish())
	{
		GWorldTime->Stop();
		Exit();
		return 0;
	}
	else
	{
		return 1;
	}
}

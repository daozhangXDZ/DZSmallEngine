#include "EngineApplication.h"
#include "LaunchEngineLoop.h"
#include "EngineGlobal.h"
#include "GameEngine.h"
#include "RHI.h"
#include "ShaderUtils.h"
#include "MoviePlayer.h"

EngineApplication* GEngineApliation = nullptr;
BaseEngine* GEngine = nullptr;
GameTimer*	GWorldTime = nullptr;



void FEngineLoop::CalculateFrameStats()
{
	//if (GEngineApliation->GetCurrMainHWD() == nullptr)
	//	return;
	//// Code computes the average frames per second, and also the 
	//// average time it takes to render one frame.  These stats 
	//// are appended to the window caption bar.

	//static int frameCnt = 0;
	//static float timeElapsed = 0.0f;

	//frameCnt++;

	//// Compute averages over one second period.
	//if ((GWorldTime->TotalTime() - timeElapsed) >= 1.0f)
	//{
	//	float fps = (float)frameCnt; // fps = frameCnt / 1
	//	float mspf = 1000.0f / fps;

	//	wstring fpsStr = to_wstring(fps);
	//	wstring mspfStr = to_wstring(mspf);

	//	wstring windowText = "BaiPaoXD SmaEngine MainEngine******£º"
	//		L"    fps: " + fpsStr +
	//		L"   mspf: " + mspfStr;

	//	SetWindowText((HWND)GEngineApliation->GetCurrMainHWD(), windowText.c_str());

	//	// Reset for next average.
	//	frameCnt = 0;
	//	timeElapsed += 1.0f;
	//}
}


FEngineLoop::FEngineLoop()
{


}

int FEngineLoop::PreInit()
{
	GEngine = new GameEngine();
	GEngineApliation = EngineApplication::get();
	GEngineApliation->Start();
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
	CalculateFrameStats();
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

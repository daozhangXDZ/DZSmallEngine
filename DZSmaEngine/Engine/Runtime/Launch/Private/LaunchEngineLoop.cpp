#include "EngineApplication.h"
#include "LaunchEngineLoop.h"
#include "EngineGlobal.h"
#include "GameEngine.h"
#include "RHI.h"
#include "D3D11/D3D11DynamicRHI.h"
#include "ShaderUtils.h"

EngineApplication* GEngineApliation = nullptr;
BaseEngine* GEngine = nullptr;
DynamicRHI* GDynamicRHI = nullptr;
GameTimer*	GWorldTime = nullptr;



void FEngineLoop::CalculateFrameStats()
{
	if (GEngineApliation->GetCurrMainHWD() == nullptr)
		return;
	// Code computes the average frames per second, and also the 
	// average time it takes to render one frame.  These stats 
	// are appended to the window caption bar.

	static int frameCnt = 0;
	static float timeElapsed = 0.0f;

	frameCnt++;

	// Compute averages over one second period.
	if ((GWorldTime->TotalTime() - timeElapsed) >= 1.0f)
	{
		float fps = (float)frameCnt; // fps = frameCnt / 1
		float mspf = 1000.0f / fps;

		wstring fpsStr = to_wstring(fps);
		wstring mspfStr = to_wstring(mspf);

		wstring windowText = "BaiPaoXD SmaEngine MainEngine******："
			L"    fps: " + fpsStr +
			L"   mspf: " + mspfStr;

		SetWindowText((HWND)GEngineApliation->GetCurrMainHWD(), windowText.c_str());

		// Reset for next average.
		frameCnt = 0;
		timeElapsed += 1.0f;
	}
}


FEngineLoop::FEngineLoop()
{


}

int FEngineLoop::PreInit()
{
	GEngine = new GameEngine();
	GEngineApliation = EngineApplication::get();
	GEngineApliation->StartApplication();
	if (1)
	{
		GDynamicRHI = new D3D11DynamicRHI();
	}
	else if (2)
	{
		GDynamicRHI = nullptr;
	}
	return 0;
}



int FEngineLoop::Init()
{
	//先初始化程序和渲染
	GEngineApliation->InitRender();
	GEngineApliation->OpenEngineWindow();
	GDynamicRHI->InitRender();	
	ShaderUtils::InitCombileAllShader();
	GEngine->Init();
	{
		GWorldTime = new GameTimer();
		GWorldTime->Reset();
		GWorldTime->Start();
	}
	
	return 0;
}


int FEngineLoop::Exit()
{
	GEngineApliation->Exit();
	GEngine->Exit();
	GDynamicRHI->Exit();
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
	GDynamicRHI->Tick();
	GEngine->Tick(GWorldTime->DeltaTime());
	if (GEngineApliation->Run() == 0)
	{
		GWorldTime->Stop();
		return 0;
	}
	else
	{
		return 1;
	}
}

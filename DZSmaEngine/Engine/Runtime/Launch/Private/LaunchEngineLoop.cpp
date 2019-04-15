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
	return 0;
}


int FEngineLoop::Exit()
{
	GEngineApliation->Exit();
	GEngine->Exit();
	GDynamicRHI->Exit();
	return 0;
}

int FEngineLoop::Tick()
{
	GDynamicRHI->Tick();
	GEngine->Tick();
	return GEngineApliation->Run();
}
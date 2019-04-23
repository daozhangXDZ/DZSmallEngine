#include "EngineApplication.h"
#include "RHISources.h"
#include "EngineGlobal.h"

EngineApplication* EngineApplication::CurrentApplication = nullptr;

EngineApplication::EngineApplication() :isStartApp(false) {}
EngineApplication* EngineApplication::get()
{
	if (CurrentApplication == nullptr)
	{
		CurrentApplication = new EngineApplication();
	}
	return CurrentApplication;
}

void EngineApplication::Start()
{
	currApplicationMisc = new EApplicationMisc();
	isStartApp = true;
}

void EngineApplication::AddWindow(EngineWindow* InEngineWindows, const bool bShowImmediately)
{
	GeneralWindow* GWin = MakeWindow(InEngineWindows, bShowImmediately);
	if (bShowImmediately)
	{
		InEngineWindows->OpenWindow();
	}
}

GeneralWindow* EngineApplication::MakeWindow(EngineWindow* InSlateWindow, const bool bShowImmediately)
{
	GeneralWindow*  vGWin = currApplicationMisc->MakerWindow();
	GeneralWindowDesc* vGWinDesc = new GeneralWindowDesc();
	vGWinDesc->width = InSlateWindow->width;
	vGWinDesc->height = InSlateWindow->height;
	vGWinDesc->title = InSlateWindow->title;
	vGWinDesc->WindowsClassName = InSlateWindow->WindowsClassName;
	vGWinDesc->titleDesc = InSlateWindow->titleDesc;
	currApplicationMisc->InitializeWindow(vGWin, vGWinDesc, nullptr, bShowImmediately);
	InSlateWindow->SetNativeWindow(vGWin);
	ActiveModalWindows.push_back(InSlateWindow);
	return vGWin;
}

void EngineApplication::Tick(float dt)
{
	TickApplication(dt);
}

void EngineApplication::DrawWindows()
{
	PrivateDrawWindows();
}


void EngineApplication::TickApplication(float dt)
{
	DrawWindows();
}

void EngineApplication::PrivateDrawWindows()
{
	for (int i=0; i < ActiveModalWindows.size(); i++)
	{
		GDynamicRHI->BeginDrawViewPort(ActiveModalWindows[i]->getViewPortRHI(), nullptr);

	}
}


void EngineApplication::Register_input(IDeviceInput_Receiver* pReceive)
{
	for (int i=0; i< ActiveModalWindows.size(); i++)
	{
		if (ActiveModalWindows[i] != nullptr)
		{
			ActiveModalWindows[i]->Register_input(pReceive);
		}
	}
}
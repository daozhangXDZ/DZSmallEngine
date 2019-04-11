#pragma once
#include "EngineWindow.h"
#include "EngineApplicationMIisc.h"
#include "EngineWindowDesc.h"
#include "GeneralApplication/DeviceInput.h"
class EngineApplication
{
public:
	EngineApplication() :isStartApp(false) {}
	static EngineApplication* get()
	{
		return new EngineApplication();
	}

	void StartApplication()
	{
		currApplication = new EApplicationMisc();
		isStartApp = true;
	}

	void InitRender() 
	{
		if (mainWindows == nullptr)
		{
			mainWindowsDesc = new EngineWindowDesc();
			mainWindowsDesc->width = 800;
			mainWindowsDesc->height = 600;
			mainWindowsDesc->title = "EngineMainWindows";
			mainWindowsDesc->titleDesc = "EngingMain";
			mainWindowsDesc->WindowsClassName = "EngineMainWindows";
			mainWindows = EngineWindow::MakeWindows(currApplication,mainWindowsDesc);
			mainWindows->InitRender();
			
		}
	}

	void OpenEngineWindow()
	{
		mainWindows->OpenWindow();
		if (currInputReceive != nullptr)
		{
			mainWindows->Register_input(currInputReceive);
		}	
	}

	bool Run()
	{
		return mainWindows->Run();
	}

	void Exit()
	{
		mainWindows->Exit();
	}

	void** GetCurrMainHWD()
	{
		return mainWindows->GetOSHandle();
	}

	void Register_input(IDeviceInput_Receiver* pReceive)
	{
		if (mainWindows != nullptr)
		{
			mainWindows->Register_input(pReceive);
		}
		currInputReceive = pReceive;
	}
	
private:
	IDeviceInput_Receiver* currInputReceive;
	EngineWindowDesc* mainWindowsDesc = nullptr;
	GeneralApplication* currApplication = nullptr;
	EngineWindow* mainWindows = nullptr;
	bool isStartApp = false;
};

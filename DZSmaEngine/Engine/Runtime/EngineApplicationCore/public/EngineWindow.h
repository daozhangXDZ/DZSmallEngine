#pragma once
#include "GeneralApplication/GeneralWindow.h"
#include "GeneralApplication/GeneralApplication.h"

class EngineWindow
{

public:
	void InitRender()
	{
		nativeWindow->InitWindows(currDesc);
	}

	bool Run()
	{
		return nativeWindow->RunWindows();
	}
	void Exit()
	{
		nativeWindow->Close();
	}

	void OpenWindow()
	{
		nativeWindow->Open();
	}

	void** GetOSHandle()
	{
		return nativeWindow->GetHWD();
	}

	void Register_input(IDeviceInput_Receiver* pReceive)
	{
		if (nativeWindow != nullptr)
		{
			nativeWindow->Register_input(pReceive);
		}
	}


public:
	static EngineWindow* MakeWindows(GeneralApplication* misc, EngineWindowDesc* desc)
	{
		EngineWindow* pw = new EngineWindow();
		pw->currDesc = desc;
		pw->nativeWindow = misc->MakerWindow(desc);
		return pw;
	};

private:
	GeneralWindow* nativeWindow;
	EngineWindowDesc* currDesc;
};
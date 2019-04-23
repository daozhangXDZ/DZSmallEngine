#pragma once
#include "GeneralApplication/GeneralWindow.h"
#include "GeneralApplication/GeneralApplication.h"

class EngineWindow
{

public:
	void SetNativeWindow(GeneralWindow* InNativeWindow)
	{
		nativeWindow = InNativeWindow;
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
private:
	GeneralWindow* nativeWindow;

public:
	int width;
	int height;
	FString title;
	FString WindowsClassName;
	FString titleDesc;
};
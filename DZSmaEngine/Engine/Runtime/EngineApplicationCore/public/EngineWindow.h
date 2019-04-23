#pragma once
#include "GeneralApplication/GeneralWindow.h"
#include "GeneralApplication/GeneralApplication.h"
#include "RHISources.h"

class EngineWindow
{

public:
	void SetNativeWindow(GeneralWindow* InNativeWindow);
	bool Run();
	void Exit();

	void SetWindowMode(bool isFullScreen);

	void OpenWindow();

	void** GetOSHandle();
	void Register_input(IDeviceInput_Receiver* pReceive);

	RHIViewPortRef getViewPortRHI();



private:
	GeneralWindow* nativeWindow;
	RHIViewPortRef ViewPortRHI;

public:
	int width;
	int height;
	FString title;
	FString WindowsClassName;
	FString titleDesc;

};
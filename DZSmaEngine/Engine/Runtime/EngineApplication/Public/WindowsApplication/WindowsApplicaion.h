#pragma once
#include "GeneralApplication/GeneralApplication.h"
#include <Windows.h>

class WindowsApplication:public GeneralApplication
{
public:
	virtual GeneralWindow* MakerWindow() override;

	virtual void InitializeWindow(GeneralWindow* Window, GeneralWindowDesc* InDefinition, GeneralWindow* InParent, const bool bShowImmediately)override;
	virtual void OpenWindow(GeneralWindow * pWin) override;
};

typedef WindowsApplication EApplicationMisc;
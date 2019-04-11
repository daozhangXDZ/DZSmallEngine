#pragma once
#include "GeneralApplication/GeneralApplication.h"
#include <Windows.h>

class WindowsApplication:public GeneralApplication
{
public:
	virtual GeneralWindow* MakerWindow(EngineWindowDesc* desc) override;

	virtual void OpenWindow(GeneralWindow * pWin) override;
};

typedef WindowsApplication EApplicationMisc;
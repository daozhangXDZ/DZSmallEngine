#pragma once
#include "GeneralWindow.h"
#include "EngineWindowDesc.h"
class GeneralApplication
{
public:
	virtual GeneralWindow* MakerWindow(EngineWindowDesc* desc)
	{
		return nullptr;
	}

	virtual void OpenWindow(GeneralWindow * pWin)
	{
		return;
	}
};
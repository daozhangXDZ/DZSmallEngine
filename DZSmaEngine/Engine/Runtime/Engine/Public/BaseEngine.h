#pragma once
#include <Windows.h>

class IEngineLoop
{
public:
	virtual void Init() = 0;
	virtual void Tick(float dt) = 0;
	virtual void Exit() = 0;
};

class BaseEngine:public IEngineLoop
{
public:
	virtual void Init() override {};
	virtual void Tick(float dt) override {};
	virtual void Exit() override {};
};
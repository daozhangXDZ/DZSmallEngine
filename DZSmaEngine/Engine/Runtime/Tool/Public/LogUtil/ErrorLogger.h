#pragma once
#include "String/StringConverter.h"
#include "COMException.h"
#include <Windows.h>
#include <string>

class ErrorLogger
{
public:
	static void Log(std::string message);
	static void Log(HRESULT hr, std::string message);
	static void Log(HRESULT hr, std::wstring message);
	static void Log(COMException & exception);
};
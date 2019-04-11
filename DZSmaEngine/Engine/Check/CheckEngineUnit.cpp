////Tutorial 2 Solution 2018-09-08
//#include "ErrorLogger.h"
//#include "RenderWindow.h"
//#pragma comment(lib,"d3d11.lib")
//#pragma comment(lib,"DirectXTK.lib")
//
//
//
//void CheckErrorlog()
//{
//	HRESULT hr = S_OK;
//	if (FAILED(hr))
//	{
//		ErrorLogger::Log(hr, " init Engine Failure");
//	}
//	else if(SUCCEEDED(hr))
//	{
//		MessageBoxA(NULL, "init Engine Success", "init Engine", 0);
//	}
//}
//
//void CheckRenderWindow(HINSTANCE hInstance)
//{
//	RenderWindow rw;
//	rw.Initialize(hInstance, "MainEngineRuntime", "MyEngineRuntimeWindowClass", 800, 600);
//	while (rw.ProcessMessages() == true)
//	{
//	}
//}
//
//int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
//	_In_opt_ HINSTANCE hPrevInstance,
//	_In_ LPWSTR    lpCmdLine,
//	_In_ int       nCmdShow)
//{
//	//CheckErrorlog();
//	CheckRenderWindow(hInstance);
//	return 0;
//}


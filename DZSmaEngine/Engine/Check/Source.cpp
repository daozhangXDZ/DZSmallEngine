////Tutorial 7 Solution 2018-09-15
//#include "Engine/Engine.h"
//#pragma comment(lib,"d3d11.lib")
//#pragma comment(lib,"DirectXTK.lib")
//
//int Engine::frameCnt = 0;
//int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
//	_In_opt_ HINSTANCE hPrevInstance,
//	_In_ LPWSTR    lpCmdLine,
//	_In_ int       nCmdShow)
//{
//	HRESULT hr = CoInitialize(NULL);
//	if (FAILED(hr))
//	{
//		ErrorLogger::Log(hr, "Failed to call CoInitialize.");
//		return -1;
//	}
//	Engine GEngine;
//	if (GEngine.Initialize(hInstance, "MainEngine", "MainEngineClass", 800, 600))
//	{
//		//engine.ShowMouseDebugInfo(true);
//		while (GEngine.ProcessMessages() == true)
//		{
//			GEngine.Run();
//		}
//		
//	}
//	return 0;
//}
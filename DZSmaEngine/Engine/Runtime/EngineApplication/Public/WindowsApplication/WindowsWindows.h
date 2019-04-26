#pragma once
#include "GeneralApplication/GeneralWindow.h"
#include "WindowContainer.h"
#include "WindowsApplicaion.h"
#include "EngineGlobal.h"

class WindowsWindow :public WindowContainer, public GeneralWindow
{
public:
	virtual void	InitWindows(GeneralWindowDesc* desc)override
	{
		this->render_window.Initialize(this, *currAppIns, desc->title, desc->WindowsClassName, desc->width, desc->height);
	};

	virtual void**  GetHWD()override
	{
		return (void **)this->render_window.GetHWND();

	};

	virtual  bool RunWindows() override
	{
		
		CalculateFrameStats();
		if (IsHasInputReceive)
		{
			while (!keyboard.CharBufferIsEmpty())
			{
				unsigned char ch = keyboard.ReadChar();
			}

			while (!keyboard.KeyBufferIsEmpty())
			{
				KeyboardEvent kbe = keyboard.ReadKey();
				unsigned char keycode = kbe.GetKeyCode();
			}


			while (!mouse.EventBufferIsEmpty())
			{
				MouseEvent me = mouse.ReadEvent();
				if (mouse.IsRightDown())
				{
					if (me.GetType() == MouseEvent::EventType::RAW_MOVE)
					{
						mInputReceive->receive_MouseMove((float)me.GetPosX(), (float)me.GetPosY());
					}
				}
			}
			if (keyboard.KeyIsPressed('W'))
			{
				mInputReceive->receive_KeyBode(EnKeyCode::W);
			}
			if (keyboard.KeyIsPressed('S'))
			{
				mInputReceive->receive_KeyBode(EnKeyCode::S);
			}
			if (keyboard.KeyIsPressed('A'))
			{
				mInputReceive->receive_KeyBode(EnKeyCode::A);
			}
			if (keyboard.KeyIsPressed('D'))
			{
				mInputReceive->receive_KeyBode(EnKeyCode::D);
			}
			if (keyboard.KeyIsPressed(VK_SPACE))
			{
				mInputReceive->receive_KeyBode(EnKeyCode::SPACE);
			}
			if (keyboard.KeyIsPressed('Z'))
			{
				mInputReceive->receive_KeyBode(EnKeyCode::Z);
			}
		}
		return this->render_window.ProcessMessages();
	};


	virtual void    Open() override
	{

	};


	virtual void    Close() override
	{

	};

	void CalculateFrameStats()
	{
		static int frameCnt = 0;
		static float timeElapsed = 0.0f;

		frameCnt++;

		// Compute averages over one second period.
		if ((GWorldTime->TotalTime() - timeElapsed) >= 1.0f)
		{
			float fps = (float)frameCnt; // fps = frameCnt / 1
			float mspf = 1000.0f / fps;

			wstring fpsStr = to_wstring(fps);
			wstring mspfStr = to_wstring(mspf);

			wstring windowText = "BaiPaoXD SmaEngine MainEngine******£º"
				L"    fps: " + fpsStr +
				L"   mspf: " + mspfStr;

			SetWindowText((HWND)GetHWD(), windowText.c_str());

			// Reset for next average.
			frameCnt = 0;
			timeElapsed += 1.0f;
		}
	}
};
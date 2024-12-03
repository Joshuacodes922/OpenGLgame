#include "OGame.h"
#include <Windows.h>
#include "Owindow.h"
OGame::OGame()
{
	m_display = std::unique_ptr <OWindow >(new OWindow());
}

OGame::~OGame()
{
	
}

void OGame::run()
{
	
	while (m_isRunning && m_display->isClosed())
	{
		MSG msg = {};
		//PM_REMOVE removes a message everytime we call peekmessage.
		if (PeekMessage(&msg, HWND(), NULL, NULL, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				m_isRunning = false;
				continue;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			Sleep(1);
		}
	}
}

void OGame::quit()
{
	m_isRunning = false;
}

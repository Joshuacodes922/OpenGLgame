#include "OGame.h"
#include "Owindow.h"
#include <Windows.h>
#include <assert.h>

/*In the Win32 API, the Window Procedure is a callback function that processes 
\messages sent to a window. Every window has an associated Window Procedure that 
determines how it responds to various events, such as user input, system commands, and window changes.*/

// Before adding this we only had the run function, and the window closed but it didn't terminate.

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) //Same syntax for all events and procedure
{
	switch (msg)
	{
		case WM_DESTROY:
			{

				OWindow* window = (OWindow*)GetWindowLongPtr(hwnd, GWLP_USERDATA); //Takes the instance.

				//Now every time we close the window, this method will be called.
				window->onDestroy();
				break;
			}


	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
}



/*wc.cbSize = sizeof(WNDCLASSEX);
The cbSize field specifies the size of the WNDCLASSEX structure in bytes. 
This is necessary because the Windows API uses it to verify the version of the
structure you're using. Setting it to sizeof(WNDCLASSEX) ensures compatibility.

wc.lpfnWndProc = DefWindowProc;
lpfnWndProc is a function pointer to the windowprocedure that processes messages sent to windows of this class.
Here, it's set to DefWindowProc, which is the default Windows message processing function. If you use this, the window won't
handle custom messages; it will only handle standard default behavior (like basic closing, resizing, etc.).*/
OWindow::OWindow()
{
	//Making of the window. You make a wc object of the WNDCLASEX class.
	WNDCLASSEX wc = {};
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpszClassName = L"JoshuaWindow";
	wc.lpfnWndProc = DefWindowProc;

	//To let the operating system know about this class, we must register it
	//RegisterClassEx(&wc);

	//We need to find a way to show when the register class fails which is why we use the assert.h header file.
	assert(RegisterClassEx(&wc));

	//As we dont want to create a window of 1024 x 768 witht eh title and everything included, and just the client window space, we must do this.
	//width = right - left.
	//Height = bottom - top
	RECT rc = { 0,0,1024,768 }; //{top,ledt,right,bottom}
	AdjustWindowRect(&rc, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,false);

	//Now we can create the window
	//WS_OVERLAPPED - Overlapped Window.
	//WS_CAPTION = title bar.
	//WS_SYSMENU = window Menu. 
	//CW_USEDDEFAULT - Lets the operating system decide the position of the window
	//Refer the few code above to understand the 7th and 8th parameters.
	m_handle = CreateWindowEx(NULL, L"JoshuaWindow", L"JoshuaWindow", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, rc.right-rc.left, rc.bottom-rc.top,NULL,NULL,NULL,NULL );
	
	assert(m_handle); //Checks if it returns anything.

	//In order to retreive window instance in the window procedure
	SetWindowLongPtr((HWND)m_handle, GWLP_USERDATA, (LONG_PTR)this);

	/*In the Win32 API, HWND (Handle to a Window) is a data type used to represent a handle to a window or a control (like a button, text box, etc.) on the screen. 
	It is essentially an identifier that the Windows operating system uses to manage and reference windows and their properties.*/
	ShowWindow((HWND)m_handle, SW_SHOW);
	UpdateWindow((HWND)m_handle);
}

OWindow::~OWindow()
{
	DestroyWindow((HWND)m_handle);
}

void OWindow::onDestroy()
{
	//We reset the handle.
	m_handle = nullptr;
}

bool OWindow::isClosed()
{
	//Returns handle. If window is null. Thw window is closed.
	return m_handle;
}

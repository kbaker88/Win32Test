#include <Windows.h>>

LRESULT CALLBACK WndProc(HWND Window, UINT Message,
	WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE Instance, HINSTANCE PrevInstance,
	LPSTR CommandLine, int CommandShow)
{
	unsigned int WindowWidth = 600, WindowHeight = 300;

	WNDCLASSEX WindowsClassStructure;
	WindowsClassStructure.cbSize = sizeof(WNDCLASSEX);
	WindowsClassStructure.style = CS_OWNDC;
	WindowsClassStructure.lpfnWndProc = WndProc;
	WindowsClassStructure.cbClsExtra = 0;
	WindowsClassStructure.cbWndExtra = 0;
	WindowsClassStructure.hInstance = Instance;
	WindowsClassStructure.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WindowsClassStructure.hCursor = LoadCursor(NULL, IDC_ARROW);
	WindowsClassStructure.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	WindowsClassStructure.lpszMenuName = NULL;
	WindowsClassStructure.lpszClassName = (const char*)"LanguageLearning";
	WindowsClassStructure.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&WindowsClassStructure))
	{
		MessageBox(NULL, "Window Registration Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 1;
	}

	HWND Window = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		(const char*)"LanguageLearning",
		"Language Learning",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT, WindowWidth, WindowHeight,
		NULL, NULL, Instance, NULL);

	if (!Window)
	{
		MessageBox(NULL, "Window Creation Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 1;
	}


	UpdateWindow(Window);
	ShowWindow(Window, CommandShow);
	
	WNDCLASSEX PaintWindow;
	
	if (!GetClassInfoEx(Instance, "TestWindow", &PaintWindow))
	{
		PaintWindow.cbSize = sizeof(WNDCLASSEX);
		PaintWindow.style = CS_OWNDC;
		PaintWindow.lpfnWndProc = WndProc;
		PaintWindow.cbClsExtra = 0;
		PaintWindow.cbWndExtra = 0;
		PaintWindow.hInstance = Instance;
		PaintWindow.hIcon = 0;
		PaintWindow.hCursor = LoadCursor(NULL, IDC_ARROW);
		PaintWindow.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		PaintWindow.lpszMenuName = NULL;
		PaintWindow.lpszClassName = "TestWindow";
		PaintWindow.hIconSm = 0;
	
		if (!RegisterClassEx(&PaintWindow))
		{
			MessageBox(NULL, "TestWindow Window Registration Failed!",
				"Error!", MB_ICONEXCLAMATION | MB_OK);
		}
	}
	
	RECT WindowRect = {};
	GetClientRect(Window, &WindowRect);
	MapWindowPoints(Window, GetParent(Window), (LPPOINT)&WindowRect, 2);
	
	HWND TestWindow = CreateWindowExW(
		WS_EX_CLIENTEDGE,
		L"TestWindow",
		L"TestWindow",
		WS_BORDER | WS_VISIBLE,
		0, 0, 300, 300,
		Window, NULL, Instance, NULL);
	
	if (TestWindow)
	{
		UpdateWindow(TestWindow);
		ShowWindow(TestWindow, SW_SHOW);
	}
	else
	{
		MessageBox(NULL, "TestWindow Window Did Not Create.",
			"Error!", MB_ICONEXCLAMATION | MB_OK);
	}
	
	HDC DeviceContext = CreateCompatibleDC(GetDC(TestWindow));
	void* Bits = 0;
	int BitmapWidth = 1024;
	int BitmapHeight = 1024;
	
	BITMAPINFO BitmapInfo = {};
	BitmapInfo.bmiHeader.biSize = sizeof(BitmapInfo.bmiHeader);
	BitmapInfo.bmiHeader.biWidth = BitmapWidth;
	BitmapInfo.bmiHeader.biHeight = BitmapHeight;
	BitmapInfo.bmiHeader.biPlanes = 1;
	BitmapInfo.bmiHeader.biBitCount = 32;
	BitmapInfo.bmiHeader.biCompression = BI_RGB;
	
	HBITMAP Bitmap = CreateDIBSection(DeviceContext,
			&BitmapInfo, DIB_RGB_COLORS, &Bits, 0, 0);
	
	SelectObject(DeviceContext, Bitmap);
	
	memset(Bits, 0xFF, BitmapWidth * BitmapHeight * sizeof(unsigned int));
	
	SetBkColor(DeviceContext, RGB(0, 0, 0));
	
	AddFontResourceExA("c:/Windows/Fonts/arial.ttf", FR_PRIVATE, 0);
	
	HFONT Font = CreateFontA(128, 0, 0, 0, FW_NORMAL,
		0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, "arial");
	
	SelectObject((HDC)DeviceContext, Font);
	
	SIZE Size;
	if (!GetTextExtentPoint32W((HDC)DeviceContext, L"T",
		1, &Size))
	{
		// TODO: Error
	}
	
	int Width = Size.cx;
	if (Width > BitmapWidth)
	{
		Width = BitmapWidth;
	}
	int Height = Size.cy;
	if (Height > BitmapHeight)
	{
		Height = BitmapHeight;
	}
	
	if (SetTextColor((HDC)DeviceContext, RGB(255, 255, 255)) ==
		CLR_INVALID)
	{
		// TODO: Error
	}
	
	if (!TextOutW((HDC)DeviceContext, 0, 0, L"T", 1))
	{
		// TODO: Error
	}
	
	BitBlt(GetDC(TestWindow), 0, 0, 250, 250,
		DeviceContext, 0, 0, SRCCOPY);
	
	DeleteObject(Bitmap);
	DeleteObject(Font);
	ReleaseDC(TestWindow, DeviceContext);

	MSG Message = {};

	while (Message.message != WM_QUIT)
	{
		if (PeekMessage(&Message, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
	}
	return 0;
}

LRESULT CALLBACK WndProc(HWND Window, UINT Message,
	WPARAM wParam, LPARAM lParam)
{
	switch (Message)
	{
	case WM_CREATE:
		break;
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	case WM_COMMAND:
	{

	} break;
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		}
	} break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(Window, Message, wParam, lParam);
	}

	return 0;
}
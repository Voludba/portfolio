#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <string>


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	HWND hwnd; // дескриптор окна
	MSG msg; // структура сообщения
	WNDCLASS w; // структура класса окна
	// Регистрация класса окна
	
	w.style = CS_HREDRAW | CS_VREDRAW;
	w.lpfnWndProc = WndProc; // имя оконной функции
	w.hInstance = hInstance;
	w.cbClsExtra = 0;
	w.cbWndExtra = 0;
	w.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	w.hCursor = LoadCursor(NULL, IDC_ARROW);
	w.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	w.lpszMenuName = NULL;
	w.lpszClassName = L"My Class";
	RegisterClass(&w);
	// Создание окна
	hwnd = CreateWindow(L"My Class", L"Окно пользователя",
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 500, 500, NULL, NULL, hInstance, NULL);
	ShowWindow(hwnd, nCmdShow); // отображение
	UpdateWindow(hwnd);          // перерисовка
	// Цикл обработки сообщений
	
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wparam, LPARAM lparam)
{
	HINSTANCE hInst;
	static HWND hBtn; // дескриптор кнопки
	


	switch (Message)
	{
	case WM_CREATE:
		hInst = ((LPCREATESTRUCT)lparam)->hInstance;
		hBtn = CreateWindow(L"button", L"Открыть файл",
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			50, 100, 120, 30, hwnd, 0, hInst, NULL);
		ShowWindow(hBtn, SW_SHOWNORMAL);
		break;
	case WM_COMMAND:
		if (lparam == (LPARAM)hBtn)    // если нажали на кнопку
		{
			ShellExecute(hwnd, L"open", L"1.docx", NULL, NULL, SW_HIDE);
		}
		return 0;
	}

		return DefWindowProc(hwnd,Message,wparam,lparam);
}
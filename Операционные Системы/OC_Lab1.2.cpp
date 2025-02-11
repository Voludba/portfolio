#include "Libs.h"
#include <vector>

HINSTANCE hInst;
static HWND hBtn, hBtn2, hBtn3;
STARTUPINFO StartupInfo = { 0 };
PROCESS_INFORMATION ProcInfo = { 0 };
std::vector <HANDLE> ProcInfoBuffer;

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
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 960, 510, NULL, NULL, hInstance, NULL);
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

	switch (Message)
	{
	case WM_CREATE:
	{
		RECT Rect,
			RectBtn;

		GetClientRect(hwnd, &Rect);
		GetClientRect(hBtn, &RectBtn);

		hInst = ((LPCREATESTRUCT)lparam)->hInstance;
		hBtn = CreateWindow(L"button",
							L"Запуск д.п.",
							WS_CHILD | WS_VISIBLE | WS_BORDER,
							(((Rect.right - Rect.left) - (RectBtn.right - RectBtn.left)) / 2) - 150,
							((Rect.bottom - Rect.top) - (RectBtn.bottom - RectBtn.top)) / 2,
							120, 30,
							hwnd, 0,
							hInst,
							NULL);
		ShowWindow(hBtn, SW_SHOWNORMAL);

		hBtn2 = CreateWindow(L"button",
							L"Закрытие д.п.",
							WS_CHILD | WS_VISIBLE | WS_BORDER,
							(((Rect.right - Rect.left) - (RectBtn.right - RectBtn.left)) / 2),
							((Rect.bottom - Rect.top) - (RectBtn.bottom - RectBtn.top)) / 2,
							120, 30,
							hwnd, 0,
							hInst,
							NULL);
		ShowWindow(hBtn2, SW_SHOWNORMAL);

		hBtn3 = CreateWindow(L"button",
							L"Выход",
							WS_CHILD | WS_VISIBLE | WS_BORDER,
							(((Rect.right - Rect.left) - (RectBtn.right - RectBtn.left)) / 2) + 150,
							((Rect.bottom - Rect.top) - (RectBtn.bottom - RectBtn.top)) / 2,
							120, 30,
							hwnd, 0,
							hInst,
							NULL);
		ShowWindow(hBtn3, SW_SHOWNORMAL);
		break;
	}


	case WM_PAINT:
		break;


	case WM_COMMAND:
	{
		DWORD dwExitCode = 0;

		if ((lparam == (LPARAM)hBtn) || (lparam == (LPARAM)hBtn2) || (lparam == (LPARAM)hBtn3))
		{
			if (lparam == (LPARAM)hBtn)
			{
				CreateProcess(L"OS_Lab_1_DP.exe",
					NULL,
					NULL,
					NULL,
					FALSE,
					0,
					NULL,
					NULL,
					&StartupInfo,
					&ProcInfo);

				ProcInfoBuffer.push_back(ProcInfo.hProcess);

				CloseHandle(ProcInfo.hThread);
			}
			else if (lparam == (LPARAM)hBtn2) 
			{ 
				if (!ProcInfoBuffer.empty())
				{
					DWORD ExitCode;

					GetExitCodeProcess(ProcInfoBuffer.back(), &ExitCode);
					if (ExitCode == STILL_ACTIVE)
					{
						TerminateProcess(ProcInfoBuffer.back(), 1);
					}
					CloseHandle(ProcInfoBuffer.back());
					ProcInfoBuffer.pop_back();
				}
			}
			else 
			{ 
				for (auto it : ProcInfoBuffer)
				{
					TerminateProcess(ProcInfoBuffer.back(), 1);
					CloseHandle(ProcInfoBuffer.back());
					ProcInfoBuffer.pop_back();
				}
				ExitProcess(1); 
			}
		}
		break;
	}

	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}	
	}

	return DefWindowProc(hwnd, Message, wparam, lparam);
}
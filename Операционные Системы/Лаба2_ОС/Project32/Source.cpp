#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "cstring"
#include <vector>
#include <iostream>
#include <fstream>
#include <shellapi.h>
#include <synchapi.h>
#include <iostream>

DWORD WINAPI PM_NO_SYNC(LPVOID lpParam);
DWORD WINAPI MP_NO_SYNC(LPVOID lpParam);
DWORD WINAPI PM_CRSECT(LPVOID lpParam);
DWORD WINAPI MP_CRSECT(LPVOID lpParam);
DWORD WINAPI PM_MUTEX(LPVOID lpParam);
DWORD WINAPI MP_MUTEX(LPVOID lpParam);

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
std::vector<int> GlobalLogThread1;
std::vector<int> GlobalLogThread2;
int In = 47, Incs = 50, Inm = 50;
CRITICAL_SECTION Sect1;

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	setlocale(LC_ALL, "Russian");
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
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1024, 1024, NULL, NULL, hInstance, NULL);
	ShowWindow(hwnd, nCmdShow); // отображение
	UpdateWindow(hwnd);          // перерисовка
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
	static HWND hBtn, hBtn1, hBtn3, hBtn4, hBtn5, hBtn7; // дескриптор кнопки
	std::ofstream file;

	HANDLE mtx = CreateMutex(NULL, false, L"Mutex");
	switch (Message)
	{
	case WM_CREATE:
		hInst = ((LPCREATESTRUCT)lparam)->hInstance;
		hBtn = CreateWindow(L"button", L"Запустить потоки",
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			100, 100, 250, 40, hwnd, 0, hInst, NULL);
		ShowWindow(hBtn, SW_SHOWNORMAL);

		hBtn3 = CreateWindow(L"button", L"Закрыть программу",
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			100, 550, 250, 40, hwnd, 0, hInst, NULL);
		ShowWindow(hBtn3, SW_SHOWNORMAL);
		hBtn4 = CreateWindow(L"button", L"Открыть файл",
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			100, 500, 250, 40, hwnd, 0, hInst, NULL);
		ShowWindow(hBtn4, SW_SHOWNORMAL);

		hBtn1 = CreateWindow(L"button", L"Удалить файл",
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			100, 450, 250, 40, hwnd, 0, hInst, NULL);
		ShowWindow(hBtn4, SW_SHOWNORMAL);


		hBtn5 = CreateWindow(L"button", L"Запустить потоки c Мьютексом",
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			400, 100, 250, 40, hwnd, 0, hInst, NULL);
		ShowWindow(hBtn, SW_SHOWNORMAL);

		hBtn7 = CreateWindow(L"button", L"Запустить потоки с крит.секцией",
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			700, 100, 250, 40, hwnd, 0, hInst, NULL);
		ShowWindow(hBtn, SW_SHOWNORMAL);

		break;
	case WM_COMMAND:

		DWORD dwExitCode = 0;

		if (lparam == (LPARAM)hBtn)    // если нажали на кнопку
		{
			HANDLE hThread[2];
			hThread[0] = CreateThread(NULL, NULL, PM_NO_SYNC, NULL, NULL, NULL);
			hThread[1] = CreateThread(NULL, NULL, MP_NO_SYNC, NULL, NULL, NULL);
			WaitForMultipleObjects(2, hThread, TRUE, INFINITE);
			CloseHandle(hThread[0]);
			CloseHandle(hThread[1]);

			file.open("1.txt", std::ios::app);
			DWORD i1;
			file << "Log 1:";
			for (i1 = 0; i1 < GlobalLogThread1.size(); ++i1)
			{
				file << GlobalLogThread1[i1] << " ";
			}
			file << "\n" << "Log 2:";
			DWORD i2;
			for (i2 = 0; i2 < GlobalLogThread2.size(); ++i2)
			{
				file << GlobalLogThread2[i2] << " ";
			}
			file << "\n";
			file.close();
			GlobalLogThread1.clear();
			GlobalLogThread2.clear();
		}

		if (lparam == (LPARAM)hBtn5)    // если нажали на кнопку
		{
			HANDLE hThread[2];
			hThread[0] = CreateThread(NULL, NULL, PM_MUTEX, NULL, NULL, NULL);
			hThread[1] = CreateThread(NULL, NULL, MP_MUTEX, NULL, NULL, NULL);
			WaitForMultipleObjects(2, hThread, TRUE, INFINITE);
			CloseHandle(hThread[0]);
			CloseHandle(hThread[1]);


			file.open("1.txt", std::ios::app);
			DWORD i1;
			file << "Log 1(Mutex):";
			for (i1 = 0; i1 < GlobalLogThread1.size(); ++i1)
			{
				file << GlobalLogThread1[i1] << " ";
			}
			file << "\n" << "Log 2(Mutex):";
			DWORD i2;
			for (i2 = 0; i2 < GlobalLogThread2.size(); ++i2)
			{
				file << GlobalLogThread2[i2] << " ";
			}
			file << "\n";
			file.close();
			GlobalLogThread1.clear();
			GlobalLogThread2.clear();
		}
		if (lparam == (LPARAM)hBtn7)    // если нажали на кнопку
		{
			HANDLE hThread[2];
			InitializeCriticalSection(&Sect1);
			hThread[0] = CreateThread(NULL, NULL, PM_CRSECT, NULL, NULL, NULL);
			hThread[1] = CreateThread(NULL, NULL, MP_CRSECT, NULL, NULL, NULL);
			WaitForMultipleObjects(2, hThread, TRUE, INFINITE);
			DeleteCriticalSection(&Sect1);
			CloseHandle(hThread[0]);
			CloseHandle(hThread[1]);
			file.open("1.txt", std::ios::app);
			DWORD i1;
			file << "Log 1(Critsec):";
			for (i1 = 0; i1 < GlobalLogThread1.size(); ++i1)
			{
				file << GlobalLogThread1[i1] << " ";
			}
			file << "\n" << "Log 2(Critsec):";
			DWORD i2;
			for (i2 = 0; i2 < GlobalLogThread2.size(); ++i2)
			{
				file << GlobalLogThread2[i2] << " ";
			}
			file << "\n";
			file.close();
			GlobalLogThread1.clear();
			GlobalLogThread2.clear();
		}

		if (lparam == (LPARAM)hBtn1)    // если нажали на кнопку
		{
			std::remove("1.txt");
		}
		if (lparam == (LPARAM)hBtn3)    // если нажали на кнопку
		{
			CloseHandle(mtx);
			ExitProcess(1);
		}
		if (lparam == (LPARAM)hBtn4)
		{
			ShellExecute(hwnd, L"open", L"1.txt", NULL, NULL, SW_RESTORE);
		}

	}

	return DefWindowProc(hwnd, Message, wparam, lparam);
}

DWORD WINAPI PM_NO_SYNC(LPVOID lpParam)
{
	DWORD i;
	for (i = 0; i < 5; ++i)
	{

		In = In + 3;
		Sleep(1);
		In = In - 3;
		GlobalLogThread1.push_back(In);
	}
	return 0;
}

DWORD WINAPI MP_NO_SYNC(LPVOID lpParam)
{
	DWORD i;
	for (i = 0; i < 5; ++i)
	{

		In = In - 3;
		Sleep(1);
		In = In + 3;
		GlobalLogThread2.push_back(In);
	}
	return 0;
}


DWORD WINAPI MP_CRSECT(LPVOID lpParam)
{
	DWORD i;
	for (i = 0; i < 5; ++i)
	{
		EnterCriticalSection(&Sect1);
		Incs = Incs - 3;
		Sleep(1);
		Incs = Incs + 3;
		GlobalLogThread2.push_back(Incs);
		LeaveCriticalSection(&Sect1);
	}
	return 0;
}

DWORD WINAPI PM_CRSECT(LPVOID lpParam)
{
	DWORD i;
	for (i = 0; i < 5; ++i)
	{
		EnterCriticalSection(&Sect1);
		Incs = Incs + 3;
		Sleep(1);
		Incs = Incs - 3;
		GlobalLogThread1.push_back(Incs);
		LeaveCriticalSection(&Sect1);
	}
	return 0;
}


DWORD WINAPI PM_MUTEX(LPVOID lpParam)
{
	HANDLE hMtx = OpenMutex(SYNCHRONIZE, false, L"Mutex");
	DWORD i;
	WaitForSingleObject(hMtx, INFINITE);
	for (i = 0; i < 5; ++i)
	{
		Inm = Inm + 3;
		Sleep(1);
		Inm = Inm - 3;
		GlobalLogThread1.push_back(Inm);
	}
	ReleaseMutex(hMtx);
	CloseHandle(hMtx);
	return 0;
}

DWORD WINAPI MP_MUTEX(LPVOID lpParam)
{
	HANDLE hMtx = OpenMutex(SYNCHRONIZE, false, L"Mutex");
	DWORD i;
	WaitForSingleObject(hMtx, INFINITE);
	for (i = 0; i < 5; ++i)
	{
		Inm = Inm - 3;
		Sleep(1);
		Inm = Inm + 3;
		GlobalLogThread2.push_back(Inm);
	}
	ReleaseMutex(hMtx);
	CloseHandle(hMtx);
	return 0;
}
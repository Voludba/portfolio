#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <synchapi.h>
#include "Cashier.h"
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


HWND hEditControl1;
HWND hEditControl2;
HWND hEditControl3;
HWND hEditControl4;
Cashier CashReg1;
Cashier CashReg2;
Cashier CashReg3;

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
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1000, 1000, NULL, NULL, hInstance, NULL);
	SetTimer(hwnd, 1001, 100, NULL);
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
	static HWND hBtn1On, hBtn1Off, hBtn2On, hBtn2Off,hBtn3On,hBtn3Off,hBtnCls, hBtnAdd; 
	static HWND hLabel1, hLabel2, hLabel3, hLabel4;
	static HWND hEditControl1, hEditControl2, hEditControl3, hEditControl4;
	int tm,queue;
	switch (Message)
	{
	case WM_CREATE:
		hInst = ((LPCREATESTRUCT)lparam)->hInstance;
		hBtn1On = CreateWindow(L"button", L"Включить первую кассу",
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			100, 100, 250, 40, hwnd, 0, hInst, NULL);
		ShowWindow(hBtn1On, SW_SHOWNORMAL);
		hBtn1Off = CreateWindow(L"button", L"Выключить первую кассу",
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			400, 100, 250, 40, hwnd, 0, hInst, NULL);
		ShowWindow(hBtn1Off, SW_SHOWNORMAL);
		hBtn2On = CreateWindow(L"button", L"Включить вторую кассу",
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			100, 150, 250, 40, hwnd, 0, hInst, NULL);
		ShowWindow(hBtn2On, SW_SHOWNORMAL);
		hBtn2Off = CreateWindow(L"button", L"Выключить вторую кассу",
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			400, 150, 250, 40, hwnd, 0, hInst, NULL);
		ShowWindow(hBtn2Off, SW_SHOWNORMAL);
		hBtn3On = CreateWindow(L"button", L"Включить третью кассу",
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			100, 200, 250, 40, hwnd, 0, hInst, NULL);
		ShowWindow(hBtn3On, SW_SHOWNORMAL);
		hBtn3Off = CreateWindow(L"button", L"Выключить третью кассу",
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			400, 200, 250, 40, hwnd, 0, hInst, NULL);
		ShowWindow(hBtn3Off, SW_SHOWNORMAL);
		hBtnCls = CreateWindow(L"button", L"Закрыть программу",
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			700, 100, 250, 40, hwnd, 0, hInst, NULL);
		ShowWindow(hBtnCls, SW_SHOWNORMAL);
		hBtnAdd = CreateWindow(L"button", L"Добавить 5 человек в очередь",
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			700, 150, 250, 40, hwnd, 0, hInst, NULL);
		ShowWindow(hBtnAdd, SW_SHOWNORMAL);
		hLabel1 = CreateWindowA("edit", "Касса 1", WS_VISIBLE | WS_CHILD | ES_MULTILINE | NULL | ES_NUMBER, 50,450, 250, 300, hwnd, NULL, NULL, NULL);
		hLabel2 = CreateWindowA("edit", "Касса 2", WS_VISIBLE | WS_CHILD | ES_MULTILINE | NULL | ES_NUMBER, 300, 450, 250, 300, hwnd, NULL, NULL, NULL);
		hLabel3 = CreateWindowA("edit", "Касса 3", WS_VISIBLE | WS_CHILD | ES_MULTILINE | NULL | ES_NUMBER, 550, 450, 250, 300, hwnd, NULL, NULL, NULL);
		hLabel4 = CreateWindowA("edit", "Людей в очереди", WS_VISIBLE | WS_CHILD | ES_MULTILINE | NULL | ES_NUMBER, 800, 450, 250, 300, hwnd, NULL, NULL, NULL);
		hEditControl1 = CreateWindowA("edit", "", WS_VISIBLE | WS_CHILD | ES_MULTILINE | NULL | ES_NUMBER, 50, 500, 250, 300, hwnd, NULL, NULL, NULL);
		hEditControl2 = CreateWindowA("edit", "", WS_VISIBLE | WS_CHILD | ES_MULTILINE | NULL | ES_NUMBER, 300, 500, 250, 350, hwnd, NULL, NULL, NULL);
		hEditControl3 = CreateWindowA("edit", "", WS_VISIBLE | WS_CHILD | ES_MULTILINE | NULL | ES_NUMBER, 550, 500, 250, 350, hwnd, NULL, NULL, NULL);
		hEditControl4 = CreateWindowA("edit", "", WS_VISIBLE | WS_CHILD | ES_MULTILINE | NULL | ES_NUMBER, 800, 500, 250, 350, hwnd, NULL, NULL, NULL);
	


		DWORD dw;

		break;
	case WM_TIMER:
		if (wparam == 1001)
		{
			WaitForSingleObject(Cashier::GetMutex(), INFINITE);
			queue = Cashier::GetQueue();
			SetWindowText(hEditControl4, std::to_wstring(queue).c_str());
			ReleaseMutex(Cashier::GetMutex());

			WaitForSingleObject(Cashier::GetMutex(),INFINITE);
			tm = CashReg1.GetTime();
			if (!CashReg1.IsRunning() && tm == 0) SetWindowText(hEditControl1, L"Не работает");
			else SetWindowText(hEditControl1, std::to_wstring(tm).c_str());
			ReleaseMutex(Cashier::GetMutex());

			WaitForSingleObject(Cashier::GetMutex(), INFINITE);
			tm = CashReg2.GetTime();
			if(!CashReg2.IsRunning() && tm == 0) SetWindowText(hEditControl2, L"Не работает");
			else SetWindowText(hEditControl2, std::to_wstring(tm).c_str());
			ReleaseMutex(Cashier::GetMutex());

			WaitForSingleObject(Cashier::GetMutex(), INFINITE);
			tm = CashReg3.GetTime();
			if(!CashReg3.IsRunning() && tm == 0) SetWindowText(hEditControl3, L"Не работает");
			else SetWindowText(hEditControl3, std::to_wstring(tm).c_str());
			ReleaseMutex(Cashier::GetMutex());
		}
		break;

	case WM_DESTROY:
		KillTimer(hwnd, 1001);
		PostQuitMessage(0);
		return 0;
	case WM_COMMAND:
		if (lparam == (LPARAM)hBtn1On) 
		{
			CashReg1.start();
		}
		if (lparam == (LPARAM)hBtn1Off)  
		{
			CashReg1.stop();
		}

		if (lparam == (LPARAM)hBtn2On)   
		{
			CashReg2.start();
		}

		if (lparam == (LPARAM)hBtn2Off)
		{
			CashReg2.stop();
		}

		if (lparam == (LPARAM)hBtn3On)   
		{
			CashReg3.start();
		}

		if (lparam == (LPARAM)hBtn3Off)
		{
			CashReg3.stop();
		}

		if (lparam == (LPARAM)hBtnAdd)
		{
			Cashier::AddQueue();
		}

		if (lparam == (LPARAM)hBtnCls)
		{
			CashReg1.stop();
			CashReg2.stop();
			CashReg3.stop();
			Cashier::CloseMtx();
			ExitThread(1);
		}
	}
	return DefWindowProc(hwnd, Message, wparam, lparam);
}


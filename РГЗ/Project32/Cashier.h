#pragma once
#include <Windows.h>
#include <string>
#include <vector>
#include <ctime>
#include <Windows.h>
#include "cstring"
#include <synchapi.h>
#include <string>

class Thr
{
	friend DWORD WINAPI ThreadProc(LPVOID lpParameter);
	HANDLE hInfo = NULL;
public:
	void Execute();
	void Close();
	bool IsRunning();

protected:
	virtual DWORD ThreadFunc() = NULL;
};

class Cashier:public Thr
{
	
private:
	HANDLE hEvent;
	static HANDLE hMtx;
	int tm; 
	static int q;
	
public:

	Cashier();
	virtual ~Cashier();

	HANDLE GetEvent();
	static HANDLE GetMutex();

	static void CloseMtx();
	void start();
	void stop();
	static void AddQueue();
	int GetTime();
	static int GetQueue();

protected:
	DWORD ThreadFunc();
};


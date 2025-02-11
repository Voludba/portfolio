#pragma once
#include "Cashier.h"

int Cashier::q = 10;
HANDLE Cashier::hMtx = CreateMutex(NULL, false, L"MTX");

extern DWORD WINAPI ThreadProc(LPVOID lpParameter)
{
	Thr* pMyThread = (Thr*)lpParameter;
	return pMyThread->ThreadFunc();
}

void Thr::Execute()
{
	this->hInfo = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProc, this, NULL, NULL);

}

bool Thr::IsRunning()
{
	if (this->hInfo != NULL) return true;
	else return false;
}

void Thr::Close()
{
	CloseHandle(this->hInfo);
	this->hInfo = NULL;
}

HANDLE Cashier::GetEvent()
{
	return this->hEvent;
}

void Cashier::start()
{
	if (IsRunning()) return;
	ResetEvent(this->GetEvent());
	Execute();
}

Cashier::~Cashier()
{
	this->stop();
	CloseHandle(this->hEvent);
}

void Cashier::AddQueue()
{
	q += 5;
}

int Cashier::GetQueue()
{
	return q;
}

Cashier::Cashier()
{
	hEvent = CreateEvent(NULL, true, false, NULL);
}

int Cashier::GetTime()
{
	return tm;
}

void Cashier::CloseMtx()
{
	CloseHandle(hMtx);
}

void Cashier::stop()
{
	if (IsRunning())
	{
		SetEvent(this->GetEvent());
		this->Close();
	}
}

HANDLE Cashier::GetMutex()
{
	return hMtx;
}

DWORD Cashier::ThreadFunc()
{
	int sl;
	srand(time(0));

	while (1)
	{
		WaitForSingleObject(hMtx, INFINITE);
		if(q>0) q--;
		ReleaseMutex(hMtx);
	    sl = 1 + rand() % 5;
		for (int i = 0; i <= sl; i++)
		{
			WaitForSingleObject(hMtx, INFINITE);
		    this->tm = sl - i;
			ReleaseMutex(hMtx);
			Sleep(1000);
		}
		if (WaitForSingleObject(this->GetEvent(), 0) == WAIT_OBJECT_0) break;
	}
	return 0;
}
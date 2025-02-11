#include <windows.h>
#include <iostream>
#include <cmath>
using namespace std;


const unsigned short SizeSqr = 20; // Сторона одного квадрата сетки в пикселях
const unsigned short NumCell = 20; // Количество квадратов сетки в столбик и строчку
const unsigned short stepX = 400; // Отступ от края консоли по горизонтали
const unsigned short stepY = 20; // Отступ от края консоли по вертикали


void drawCirc(HDC* hdc, int x, int y) {
	for (int j = 0; j < 19; j++) {
		for (int i = 0; i < 19; i++) {
			if ((i - 9) * (i - 9) + (j - 9) * (j - 9) <= 72)
				SetPixel(*hdc, 1 + j + stepX + x * 20, 1 + i + stepY + y * 20, RGB(0, 255, 0));
		}
	}
}


void drawBrez(HDC* hdc, int X1, int Y1, int X2, int Y2) {
	int dx, dy, e, dx2, dy2;
	bool ch = false;
	X2 -= X1;
	Y2 -= Y1;
	dx = abs(X2);
	dy = abs(Y2);

	if (X2 == 0 && Y2 == 0) {
		std::cin.ignore();
		return;
	}

	if (X2) X2 = X2 < 0 ? -1 : 1;
	if (Y2) Y2 = Y2 < 0 ? -1 : 1;
	if (dy > dx) { int t = dy; dy = dx; dx = t; ch = true; }
	dx2 = dx << 1;
	dy2 = dy << 1;
	e = dy2 - dx;

	for (int i = 0; i <= dx; i++) {
		drawCirc(hdc, X1, Y1);
		if (e >= 0) { if (ch) X1 += X2; else Y1 += Y2; e -= dx2; if (i != dx) i--; }
		else { if (ch) Y1 += Y2; else X1 += X2; e += dy2; }
	}
}


int main() {
	setlocale(LC_ALL, "RUS");
	HWND hwnd = GetConsoleWindow();
	HDC hdc = GetDC(hwnd);
	HDC* dc = &hdc;
	HPEN hpen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	SelectObject(hdc, hpen);

	for (int i = 0; i <= NumCell; i += 1) {
		MoveToEx(hdc, stepX + i * SizeSqr, stepY, NULL);
		LineTo(hdc, stepX + i * SizeSqr, stepY + NumCell * SizeSqr);
		MoveToEx(hdc, stepX, stepY + i * SizeSqr, NULL);
		LineTo(hdc, stepX + NumCell * SizeSqr, stepY + i * SizeSqr);
	}


	int a = 0;
	int *ArrXPoints = new int[a];
	int *ArrYPoints = new int[a];
	int XminP = 20, XmaxP = -1, YminP = 20, YmaxP = -1;

	cout << "Количество вершин: ";
	cin >> a;

	for (int i = 0; i < a; i++) {
		cout << "Координаты " << i + 1 << " вершины: ";
		cin >> ArrXPoints[i];
		cin >> ArrYPoints[i];
		if (ArrXPoints[i] < XminP) XminP = ArrXPoints[i];
		if (ArrYPoints[i] < YminP) YminP = ArrYPoints[i];
		if (ArrXPoints[i] > XmaxP) XmaxP = ArrXPoints[i];
		if (ArrYPoints[i] > YmaxP) YmaxP = ArrYPoints[i];
		if (i != 0) drawBrez(dc, ArrXPoints[i - 1], ArrYPoints[i - 1], ArrXPoints[i], ArrYPoints[i]);
	}

	drawBrez(dc, ArrXPoints[a - 1], ArrYPoints[a - 1], ArrXPoints[0], ArrYPoints[0]);

	for (int j = XminP; j <= XmaxP; j++) {
		COLORREF c;
		bool zalivat = false;
		int i, ik;

		for (i = YminP; i <= YmaxP; i++) {
			c = GetPixel(hdc, stepX + 10 + j * 20, stepY + 10 + i * 20);
			if (c == RGB(0, 255, 0)) break;
		}

		for (ik = YmaxP; ik >= YminP; ik--) {
			c = GetPixel(hdc, stepX + 10 + j * 20, stepY + 10 + ik * 20);
			if (c == RGB(0, 255, 0)) break;
		}

		while (i < ik) {
			c = GetPixel(hdc, stepX + 10 + j * 20, stepY + 10 + i * 20);
			if (zalivat && c == RGB(0, 255, 0) && GetPixel(hdc, stepX + 10 + j * 20, stepY + 10 + (i - 1) * 20) != RGB(0, 255, 0)) zalivat = false;
			else if (!zalivat && c == RGB(0, 255, 0) && GetPixel(hdc, stepX + 10 + j * 20, stepY + 10 + (i - 1) * 20) != RGB(0, 255, 0)) zalivat = true;
			if (c != RGB(0, 255, 0) && zalivat) drawCirc(dc, j, i);
			i++;
		}
	}


	ReleaseDC(hwnd, hdc);
	cin.get();
	cin.ignore();
	system("pause");
}
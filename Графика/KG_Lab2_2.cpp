#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <Windows.h>
#include <locale.h>
using namespace std;

double vert[50][3];
int faces[50][4];
int scount, fcount = 0;
int k = 200, xz = 400, yz = 400;
double result[4][4] = { { 1.000000, 0.000000, 0.000000, 0 },
						{ 0.000000, 1.000000, 0.000000, 0 },
						{ 0.000000, 0.000000, 1.000000, 0 },
						{ 0.000000, 0.000000, 0.000000, 1 } };

HWND hWnd = GetConsoleWindow();
HDC dc = GetDC(hWnd);

void Clear()
{
	HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
	SelectObject(dc, brush);
	Rectangle(dc, 0, 0, 2500, 1480);
	DeleteObject(brush);
}

double flatVector(double x1, double x2, double x3, double y1, double y2, double y3, double z1, double z2, double z3)
{

	double A = (y2 - y1) * (z3 - z1) - (y3 - y1) * (z2 - x1);
	double B = (x3 - x1) * (z2 - z1) - (x2 - x1) * (z3 - z1);
	double C = (x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1);

	return C;
}

void print()
{
	HPEN pen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));

	int x1, y1, x0, y0, dot;
	x0 = xz;
	y0 = yz;

	SelectObject(dc, pen);

	for (int i = 0; i <= fcount; i++) {
		double x[4];
		double y[4];
		double z[4];

		x[0] = (int)((vert[faces[i][0] - 1][0] * result[0][0] + vert[faces[i][0] - 1][1] * result[1][0] + vert[faces[i][0] - 1][2] * result[2][0] + result[0][3]) * k);
		y[0] = (int)((vert[faces[i][0] - 1][0] * result[0][1] + vert[faces[i][0] - 1][1] * result[1][1] + vert[faces[i][0] - 1][2] * result[2][1] + result[1][3]) * k);
		z[0] = (int)((vert[faces[i][0] - 1][0] * result[0][2] + vert[faces[i][0] - 1][1] * result[1][2] + vert[faces[i][0] - 1][2] * result[2][2] + result[1][3]) * k);

		x[1] = (int)((vert[faces[i][1] - 1][0] * result[0][0] + vert[faces[i][1] - 1][1] * result[1][0] + vert[faces[i][1] - 1][2] * result[2][0] + result[0][3]) * k);
		y[1] = (int)((vert[faces[i][1] - 1][0] * result[0][1] + vert[faces[i][1] - 1][1] * result[1][1] + vert[faces[i][1] - 1][2] * result[2][1] + result[1][3]) * k);
		z[1] = (int)((vert[faces[i][1] - 1][0] * result[0][2] + vert[faces[i][1] - 1][1] * result[1][2] + vert[faces[i][1] - 1][2] * result[2][2] + result[1][3]) * k);

		x[2] = (int)((vert[faces[i][2] - 1][0] * result[0][0] + vert[faces[i][2] - 1][1] * result[1][0] + vert[faces[i][2] - 1][2] * result[2][0] + result[0][3]) * k);
		y[2] = (int)((vert[faces[i][2] - 1][0] * result[0][1] + vert[faces[i][2] - 1][1] * result[1][1] + vert[faces[i][2] - 1][2] * result[2][1] + result[1][3]) * k);
		z[2] = (int)((vert[faces[i][2] - 1][0] * result[0][2] + vert[faces[i][2] - 1][1] * result[1][2] + vert[faces[i][2] - 1][2] * result[2][2] + result[1][3]) * k);

		x[3] = (int)((vert[faces[i][3] - 1][0] * result[0][0] + vert[faces[i][3] - 1][1] * result[1][0] + vert[faces[i][3] - 1][2] * result[2][0] + result[0][3]) * k);
		y[3] = (int)((vert[faces[i][3] - 1][0] * result[0][1] + vert[faces[i][3] - 1][1] * result[1][1] + vert[faces[i][3] - 1][2] * result[2][1] + result[1][3]) * k);
		z[3] = (int)((vert[faces[i][3] - 1][0] * result[0][2] + vert[faces[i][3] - 1][1] * result[1][2] + vert[faces[i][3] - 1][2] * result[2][2] + result[1][3]) * k);

		double flat = flatVector(x[0], x[1], x[2], y[0], y[1], y[2], z[0], z[1], z[2]);
		if (flat * (-1) >= 0) {

			for (int ii = 0; ii < 4; ii++)
			{
				if (ii == 3) {
					MoveToEx(dc, x0 + x[3], y0 + y[3], NULL);
					LineTo(dc, x0 + x[0], y0 + y[0]);

				}
				else {

					MoveToEx(dc, x0 + x[ii], y0 + y[ii], NULL);
					ii++;


					LineTo(dc, x0 + x[ii], y0 + y[ii]);
					ii--;
				}
			}
		}
	}
	DeleteObject(pen);


}

void Vvod()
{
	
	for (int i = 0; i < 50; i++)
		for (int j = 0; j < 3; j++)
			vert[i][j] = 0;
	for (int i = 0; i < 50; i++)
		for (int j = 0; j < 4; j++)
			faces[i][j] = 0;

	int it, n = 0, m = 0, minus = 0, counter;
	char buff[255];
	FILE* fp = fopen("cube.obj", "r");
	if (!fp)
	{
		cout << "Error open file: " << endl;
	}
	else
	{
		cout << "succes " << endl;
	}
	while (fgets(buff, 255, fp))
	{
		if (buff[0] == 'v')
		{
			it = 0;
			counter = 2;
			for (int j = 0; j < 3; j++)
			{
				if (buff[counter] == '-')
				{
					minus = 1;
					counter++; 
				}
				else minus = 0;


				for (int i = counter; (buff[i] != '.') && (buff[i] != ' ') && (buff[i] != '\0'); i++)it++; 
				for (counter; (buff[counter] != ' ') && (buff[counter] != '\0'); counter++) 
				{
					if (buff[counter] != '.')
					{
						if (minus)
							vert[m][j] -= ((int)buff[counter] - 48) * pow(10, it - 1);
						else
							vert[m][j] += ((int)buff[counter] - 48) * pow(10, it - 1);
						it--; 
					}
				}
				counter++; 
				it = 0;
			}
			m++; 
		}

		if (buff[0] == 'f')
		{
			it = 0; 
			counter = 2;
			for (int j = 0; j < 4; j++)
			{
				for (counter; (buff[counter] != ' ') && (buff[counter] != '\0'); counter++)
				{
					faces[n][j] += (int)buff[counter] - 48;

				}
				counter++; 
			}
			n++;
		}


	}
	fclose(fp);
	scount = m; // РЎРѕС…СЂР°РЅСЏРµРј РєРѕР»РёС‡РµСЃС‚РІРѕ СЃС‚СЂРѕРє "С‚СЂРѕРµРє РєРѕРѕСЂРґРёРЅР°С‚" РІ РјР°СЃСЃРёРІРµ
	fcount = n; // РЎРѕС…СЂР°РЅСЏРµРј РєРѕР»РёС‡РµСЃС‚РІРѕ "С‡РµС‚РІС‘СЂРѕРє РЅРѕРјРµСЂРѕРІ РєРѕРѕСЂРґРёРЅР°С‚" РІ РјР°СЃСЃРёРІРµ

}

void mul(double B[][4])
{
	double C[4][4] = { {0.0, 0.0, 0.0, 0.0},{0.0, 0.0, 0.0, 0.0},	{0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0} };
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{

			for (int k = 0; k < 4; k++)
				C[i][j] += result[i][k] * B[k][j];
		}
	}

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			result[i][j] = C[i][j];

}

void scale(double s) 
{


	double S[4][4] = { {s, 0.0, 0.0, 0},
						{0.0, s, 0.0, 0},
						{0.0, 0.0,s, 0},
						{0.0, 0.0, 0.0, 1} };
	mul(S);
}
void rotateX() {

	double Rx[4][4] = { {1.000000, 0.000000, 0.000000, 0},
						{0.000000, 0.984808, 0.173648, 0},
						{0.000000, -0.173648, 0.984808, 0},
						{0.000000, 0.000000, 0.000000, 1} };
	mul(Rx);
}
void rotateY() {

	double Ry[4][4] = { {0.984808, 0.000000, -0.173648, 0},
						{0.000000, 1.000000, 0.000000, 0},
						{0.173648, 0.000000, 0.984808, 0},
						{0.000000, 0.000000, 0.000000, 1} };

	mul(Ry);
}
void Dislocate(double  dx, double dy, double dz) {
	result[0][3] = dx;
	result[1][3] = dy;
}


int main()
{
	double dx = 0;
	double dy = 0;
	double dz = 0;
	Vvod();
	Clear();
	print();

	while (1 > 0) {

		if (GetAsyncKeyState(VK_LCONTROL) < 0) {
			Sleep(50);
			double sx = 1.1;
			Clear();
			scale(sx);
			print();
		}
		if (GetAsyncKeyState(VK_RCONTROL) < 0) {
			Sleep(50);
			double sx = 0.9;
			Clear();
			scale(sx);
			print();
		}
		if (GetAsyncKeyState(VK_LSHIFT) < 0) {
			Sleep(50);
			Clear();
			rotateX();
			print();
		}
		if (GetAsyncKeyState(VK_RSHIFT) < 0) {
			Sleep(50);
			Clear();
			rotateY();
			print();
		}
		if (GetAsyncKeyState(VK_RIGHT) < 0) {
			dx += 0.3;
			Sleep(50);
			Clear();
			Dislocate(dx, dy, dz);
			//break;
			print();
		}
		if (GetAsyncKeyState(VK_LEFT) < 0) {
			dx -= 0.3;
			Sleep(50);
			Clear();
			Dislocate(dx, dy, dz);
			print();
		}
		if (GetAsyncKeyState(VK_DOWN) < 0) {
			dy += 0.3;
			Sleep(50);
			Clear();
			Dislocate(dx, dy, dz);
			print();
		}
		if (GetAsyncKeyState(VK_UP) < 0) {
			dy -= 0.3;
			Sleep(50);
			Clear();
			Dislocate(dx, dy, dz);
			print();
		}
	}
}
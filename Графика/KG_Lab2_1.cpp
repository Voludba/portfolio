#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <Windows.h>
#include <locale.h>
using namespace std;

double vert[50][3];//Вершины
int faces[50][4];// Плоскости
int scount, fcount = 0;
int k = 200, xz = 400, yz = 400;
double result[4][4] = { { 1.000000, 0.000000, 0.000000, 0 },
						{ 0.000000, 1.000000, 0.000000, 0 },
						{ 0.000000, 0.000000, 1.000000, 0 },
						{ 0.000000, 0.000000, 0.000000, 1 } };

HWND hWnd = GetConsoleWindow();//ориентир на консольное окно
HDC dc = GetDC(hWnd);//подключение к консольному окну

void Clear()
{
	HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
	SelectObject(dc, brush);
	Rectangle(dc, 0, 0, 2500, 1480);
	DeleteObject(brush);
}

void print()
{
	HPEN pen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));

	int x1, y1, x0, y0, dot;
	x0 = xz;
	y0 = yz;

	SelectObject(dc, pen);//выбор пера для контура

	for (int i = 0; i <= fcount; i++) {


		for (int ii = 0; ii < 4; ii++)
		{
			if (ii == 3) {
				dot = faces[i][ii] - 1;

				x1 = (int)((vert[dot][0] * result[0][0] + vert[dot][1] * result[1][0] + vert[dot][2] * result[2][0] + result[0][3]) * k);

				y1 = (int)((vert[dot][0] * result[0][1] + vert[dot][1] * result[1][1] + vert[dot][2] * result[2][1] + result[1][3]) * k);
				MoveToEx(dc, x0 + x1, y0 + y1, NULL);

				dot = faces[i][0] - 1;

				x1 = (int)((vert[dot][0] * result[0][0] + vert[dot][1] * result[1][0] + vert[dot][2] * result[2][0] + result[0][3]) * k);

				y1 = (int)((vert[dot][0] * result[0][1] + vert[dot][1] * result[1][1] + vert[dot][2] * result[2][1] + result[1][3]) * k);
				LineTo(dc, x0 + x1, y0 + y1);

			}
			else {
				dot = faces[i][ii] - 1;

				x1 = (int)((vert[dot][0] * result[0][0] + vert[dot][1] * result[1][0] + vert[dot][2] * result[2][0] + result[0][3]) * k);

				y1 = (int)((vert[dot][0] * result[0][1] + vert[dot][1] * result[1][1] + vert[dot][2] * result[2][1] + result[1][3]) * k);
				MoveToEx(dc, x0 + x1, y0 + y1, NULL);
				ii++;

				dot = faces[i][ii] - 1;

				x1 = (int)((vert[dot][0] * result[0][0] + vert[dot][1] * result[1][0] + vert[dot][2] * result[2][0] + result[0][3]) * k);

				y1 = (int)((vert[dot][0] * result[0][1] + vert[dot][1] * result[1][1] + vert[dot][2] * result[2][1] + result[1][3]) * k);
				LineTo(dc, x0 + x1, y0 + y1);
				ii--;
			}
		}
	}

	DeleteObject(pen);//освобождение памяти, псле использования пера


}

void Input()
{


	// Обнуляем матрицы вершин и линий для перевода в int.
	for (int i = 0; i < 50; i++)
		for (int j = 0; j < 3; j++)
			vert[i][j] = 0;
	for (int i = 0; i < 50; i++)
		for (int j = 0; j < 4; j++)
			faces[i][j] = 0;

	int it, n = 0, m = 0, minus = 0, counter;
	char buff[255];
	FILE* fp = fopen("cube.obj", "r");// Здесь могло быть ваше имя файла
	if (!fp) //проверка на открытие файла
	{
		cout << "Error open file: " << endl;
	}
	else
	{
		cout << "succes " << endl;
	}
	while (fgets(buff, 255, fp)) // Желательно иметь пробел после строки , возможно, из-за этого может проскакивать ошибка
	{
		if (buff[0] == 'v')
		{
			it = 0;
			counter = 2; // Пропускаем обозначение "v:"
			for (int j = 0; j < 3; j++)
			{
				if (buff[counter] == '-')
				{
					minus = 1;
					counter++; // пропускаем минус, не считаем его за цифру
				}
				else minus = 0;


				for (int i = counter; (buff[i] != '.') && (buff[i] != ' ') && (buff[i] != '\0'); i++)it++; //Подсчёт количества символов до точки в первом элементе
				for (counter; (buff[counter] != ' ') && (buff[counter] != '\0'); counter++) // Идём по смещённому началу и переводим char* в инт
				{
					if (buff[counter] != '.')
					{
						if (minus)
							vert[m][j] -= ((int)buff[counter] - 48) * pow(10, it - 1);
						else
							vert[m][j] += ((int)buff[counter] - 48) * pow(10, it - 1);
						it--; // Можно сказать, что это номер цифры в нашем числе, если it = -1 , значит число после запятой
					}
				}
				counter++; // Переход к новой координате в строке (т.к. мы остановились в разрыве между ними)
				it = 0;
			}
			m++; // Номер строки увеличиваем
		}

		if (buff[0] == 'f')
		{
			it = 0; //Пропускаем обозначение "f:"
			counter = 2;
			for (int j = 0; j < 4; j++)
			{
				for (counter; (buff[counter] != ' ') && (buff[counter] != '\0'); counter++) // Идём по смещённому началу и переводим char* в инт
				{
					faces[n][j] += (int)buff[counter] - 48;

				}
				counter++; // Переход к новой координате в строке (т.к. мы остановились в разрыве между ними)
			}
			n++;
		}


	}
	fclose(fp);
	scount = m; // Сохраняем количество строк "троек координат" в массиве
	fcount = n; // Сохраняем количество "четвёрок номеров координат" в массиве

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

void scale(double s) // Функция для умножения результируюей матрицы на коэффициент Масштаба S
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
	Input();
	Clear();
	print();

	while (true) {

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
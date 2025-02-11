#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <Windows.h>
#include <locale.h>//библиотека для русского языка

const int shift = 100;//сдвиг сетки вниз
const int cells = 20; // размер ячейки в пикселях
const int celln = 20; // количество ячеек 

HWND hwnd = GetConsoleWindow();//ориентир на консольное окно
HDC dc = GetDC(hwnd);//подключение к консольному окну

void DrawPoint(double cx, double cy) {//функция отрисовки круга в клеточке

	HBRUSH brush = CreateSolidBrush(RGB(153, 50, 204));//кисть
	HPEN pen1 = CreatePen(PS_NULL, 1, RGB(0, 0, 0));//создание пера, которым будет рисоваться контура круга

	SelectObject(dc, brush);//выбор кисти для закрашивания круга
	SelectObject(dc, pen1);//выбор пера для контура круга
	Ellipse(dc, (cx - 1) * cells + cx + (celln/2)*cells + (celln / 2) - (cells/2), shift + (celln - cy) * cells + celln - cy + 1 - (celln / 2) * cells - (celln / 2) - (cells / 2),
		cx * cells + cx + (celln / 2) * cells + (celln / 2) - (cells / 2), shift + (celln - cy + 1) * cells + celln - cy + 1 - (celln / 2) * cells - (celln / 2) - (cells / 2));//задание коорданат квадрата, в котором нужно нарисовать круг
	DeleteObject(brush);//освобождение памяти, псле использования кисти
	DeleteObject(pen1);//освобождение памяти, псле использования пера
}


void DrawNet() {//функция отрисовки сетки
	int x = 0, y = 0;//вспомогательные переменные

	HPEN pen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));//создание пера для отрисовки сетки

	//отрисовка вертикальных линий
	SelectObject(dc, pen);//выбор пера для сетки
	while (x <= celln) {
		MoveToEx(dc, x * cells + x, shift, 0);//перенос текущей позиции
		LineTo(dc, x * cells + x, shift + cells * celln + celln);//провести линию
		x++;
	}
	DeleteObject(pen);//освобождение памяти, псле использования пера

	//отрисовка горизонтальных линий
	SelectObject(dc, pen);//выбор пера для сетки
	while (y <= celln) {
		MoveToEx(dc, 0, shift + y * cells + y, 0);//перенос текущей позиции
		LineTo(dc, cells * celln + celln, shift + y * cells + y);//провести линию
		y++;
	}
	DeleteObject(pen);//освобождение памяти, после использования пера
}


void Ymn(double A[][4], double B[][4])
{
	double C[4][4];
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			C[i][j] = 0;
			for (int k = 0; k < 4; k++)
				C[i][j] += A[i][k] * B[k][j];
		}
	}

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			A[i][j] = C[i][j];

}

void Polygon(double P[][4]) 
{
	HPEN pen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	
	SelectObject(dc, pen);//выбор пера для контура круга

	
	for (int i = 0; i < 3; i++) 
	{
		MoveToEx(dc, (P[i][0] - 1) * cells + P[i][0] + (celln / 2) * cells + (celln / 2), shift + (celln - P[i][1]) * cells + celln - P[i][1] + 1 - (celln / 2) * cells - (celln / 2), 0);
		LineTo(dc, (P[i+1][0] - 1) * cells + P[i+1][0] + (celln / 2) * cells + (celln / 2), shift + (celln - P[i+1][1]) * cells + celln - P[i+1][1] + 1 - (celln / 2) * cells - (celln / 2));
	}
	

	DeleteObject(pen);//освобождение памяти, псле использования пера
}


void VecYmn(double A[][4], double B[][4])
{

	double C[4][4];

	for (int i = 0; i < 4; i++)
		A[i][3] = 1;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			C[i][j] = 0;

			for (int k = 0; k < 4; k++)
				C[i][j] += A[i][k] * B[k][j];
		}
	}

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			A[i][j] = C[i][j];

}

void Clear()
{
	HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
	SelectObject(dc, brush);
	Rectangle(dc, 0, 0, 600, 600);
	DeleteObject(brush);
}

int main()
{

	int Vert[3][8];//координаты вершин
	int Pol[4][6];//массив полигонов

	//FILE* file;
	//fopen_s(&file, , "rt");
	//char buff[256];

	

	double Pol1[4][4] = { {1.000000, -1.000000, -1.000000, 0},
						  {1.000000, -1.000000, 1.000000, 0},
						  {-1.000000, -1.000000, 1.000000, 0},
						  {-1.000000, -1.000000, -1.000000, 1} };

	double Pol2[4][4] = { {1.000000, 1.000000, - 0.999999, 0},
						  {-1.000000, 1.000000, - 1.000000, 0},
						  {-1.000000, 1.000000, 1.000000, 0},
						  {0.999999, 1.000000, 1.000001, 1} };

	double Pol3[4][4] = { {1.000000, - 1.000000, - 1.000000, 0},
						  {1.000000, 1.000000, - 0.999999, 0},
						  {0.999999, 1.000000, 1.000001, 0},
						  {1.000000, -1.000000, 1.000000, 1} };

	double Pol4[4][4] = { {1.000000, -1.000000, 1.000000, 0},
						  {0.999999, 1.000000, 1.000001, 0},
						  {-1.000000, 1.000000, 1.000000, 0},
						  {-1.000000, - 1.000000, 1.000000, 1} };

	double Pol5[4][4] = { {-1.000000, - 1.000000, 1.000000, 0},
						  {-1.000000, 1.000000, 1.000000, 0},
						  {-1.000000, 1.000000, - 1.000000, 0},
						  {-1.000000, - 1.000000, - 1.000000, 1} };

	double Pol6[4][4] = { {1.000000, 1.000000, - 0.999999, 0},
						  {1.000000, - 1.000000, - 1.000000, 0},
						  {-1.000000, - 1.000000, - 1.000000, 0},
						  {-1.000000, 1.000000, - 1.000000, 1} };


	double dx=2, dy=0, dz=0;
	double sx = 2, sy = 2, sz = 2;
	double fi = 45 * M_PI / 180;
	double a = 30 * M_PI / 180;
	//матрица сдвига 
	double T[4][4]={ {1, 0, 0, 0},
					 {0, 1, 0, 0},
					 {0, 0, 1, 0},
					 {dx, dy, dz, 1} }; 
	//матрица масштабировния
	double S[4][4]= { {sx, 0, 0, 0},
					 {0, sy, 0, 0},
					 {0, 0, sz, 0},
					 {0, 0, 0, 1} };
	//матрица вращения по оси X
	double Rx[4][4]= { {1, 0, 0, 0},
					 {0, cos(fi), sin(fi), 0},
					 {0, -sin(fi), cos(fi), 0},
					 {0, 0, 0, 1} };
	//матрица вращения по оси Y
	double Ry[4][4] = { {cos(fi), 0, -sin(fi), 0},
					 {0, 1, 0, 0},
					 {sin(fi), 0, cos(fi), 0},
					 {0, 0, 0, 1} };
	//матрица вращения по оси Z
	double Rz[4][4] = { {cos(fi), sin(fi), 0, 0},
					 {-sin(fi), cos(fi), 0, 0},
					 {0, 0, 1, 0},
					 {0, 0, 0, 1} };
	//матрица центральной проекции
	double M[4][4] = { {1, 0, 0, 0},
					 {0, 1, 0, 0},
					 {0, 0, 1, 1},
					 {0, 0, 0, 1} };

	double Pol7[4][4] = { {1.000000, -1.000000, -1.000000, 0},
						  {1.000000, -1.000000, 1.000000, 0},
						  {-1.000000, -1.000000, 1.000000, 0},
						  {-1.000000, -1.000000, -1.000000, 1} };

	

	for (double fi=0 * M_PI /180; fi>-1; fi+=1* M_PI /180)
	{
		double Pol1[4][4] = { {1.000000, -1.000000, -1.000000, 0},
						  {1.000000, -1.000000, 1.000000, 0},
						  {-1.000000, -1.000000, 1.000000, 0},
						  {-1.000000, -1.000000, -1.000000, 1} };

		double Pol2[4][4] = { {1.000000, 1.000000, -0.999999, 0},
							  {-1.000000, 1.000000, -1.000000, 0},
							  {-1.000000, 1.000000, 1.000000, 0},
							  {0.999999, 1.000000, 1.000001, 1} };

		double Pol3[4][4] = { {1.000000, -1.000000, -1.000000, 0},
							  {1.000000, 1.000000, -0.999999, 0},
							  {0.999999, 1.000000, 1.000001, 0},
							  {1.000000, -1.000000, 1.000000, 1} };

		double Pol4[4][4] = { {1.000000, -1.000000, 1.000000, 0},
							  {0.999999, 1.000000, 1.000001, 0},
							  {-1.000000, 1.000000, 1.000000, 0},
							  {-1.000000, -1.000000, 1.000000, 1} };

		double Pol5[4][4] = { {-1.000000, -1.000000, 1.000000, 0},
							  {-1.000000, 1.000000, 1.000000, 0},
							  {-1.000000, 1.000000, -1.000000, 0},
							  {-1.000000, -1.000000, -1.000000, 1} };

		double Pol6[4][4] = { {1.000000, 1.000000, -0.999999, 0},
							  {1.000000, -1.000000, -1.000000, 0},
							  {-1.000000, -1.000000, -1.000000, 0},
							  {-1.000000, 1.000000, -1.000000, 1} };

		double Rx[4][4] = { {1, 0, 0, 0},
					 {0, cos(fi), sin(fi), 0},
					 {0, -sin(fi), cos(fi), 0},
					 {0, 0, 0, 1} };

		double Ry[4][4] = { {cos(fi), 0, -sin(fi), 0},
					 {0, 1, 0, 0},
					 {sin(fi), 0, cos(fi), 0},
					 {0, 0, 0, 1} };

		double Rz[4][4] = { {cos(fi), sin(fi), 0, 0},
						 {-sin(fi), cos(fi), 0, 0},
						 {0, 0, 1, 0},
						 {0, 0, 0, 1} };


		
		Ymn(Pol1, M);
		Ymn(Pol2, M);
		Ymn(Pol3, M);
		Ymn(Pol4, M);
		Ymn(Pol5, M);
		Ymn(Pol6, M);

		
		VecYmn(Pol1, T);
		VecYmn(Pol2, T);
		VecYmn(Pol3, T);
		VecYmn(Pol4, T);
		VecYmn(Pol5, T);
		VecYmn(Pol6, T);
		

		Ymn(Pol1, S);
		Ymn(Pol2, S);
		Ymn(Pol3, S);
		Ymn(Pol4, S);
		Ymn(Pol5, S);
		Ymn(Pol6, S);
		
		
		Ymn(Pol1, Rx);
		Ymn(Pol2, Rx);
		Ymn(Pol3, Rx);
		Ymn(Pol4, Rx);
		Ymn(Pol5, Rx);
		Ymn(Pol6, Rx);
		
		Ymn(Pol1, Ry);
		Ymn(Pol2, Ry);
		Ymn(Pol3, Ry);
		Ymn(Pol4, Ry);
		Ymn(Pol5, Ry);
		Ymn(Pol6, Ry);
		
		Ymn(Pol1, Rz);
		Ymn(Pol2, Rz);
		Ymn(Pol3, Rz);
		Ymn(Pol4, Rz);
		Ymn(Pol5, Rz);
		Ymn(Pol6, Rz);
		
		for (int i = 0; i < 4; i++) {
			DrawPoint(Pol1[i][0], Pol1[i][1]);
			DrawPoint(Pol2[i][0], Pol2[i][1]);
			DrawPoint(Pol3[i][0], Pol3[i][1]);
			DrawPoint(Pol4[i][0], Pol4[i][1]);
			DrawPoint(Pol5[i][0], Pol5[i][1]);
			DrawPoint(Pol6[i][0], Pol6[i][1]);
		}

		Polygon(Pol1);
		Polygon(Pol2);
		Polygon(Pol3);
		Polygon(Pol4);
		Polygon(Pol5);
		Polygon(Pol6);

		Sleep(50);

		Clear();
		
	}

}

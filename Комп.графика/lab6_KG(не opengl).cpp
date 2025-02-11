#define NOMINMAX

#include <iostream>
#include <Windows.h>
#include <cmath>
#include <algorithm>

const int shift = 130;//сдвиг сетки вниз
const int cells = 8; // размер ячейки в пикселях
const int celln = 80; // количество ячеек 

int colour = 1; //цвет каждой фигуры
int field[celln][celln];//массив точек на сетке

HWND hwnd = GetConsoleWindow();//ориентир на консольное окно
HDC dc = GetDC(hwnd);//подключение к консольному окну

HPEN pen_net = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));//перо сетки

HBRUSH brush_point = CreateSolidBrush(RGB(153, 50, 204));//кисть точки
HPEN pen_point = CreatePen(PS_NULL, 1, RGB(0, 0, 0));//перо точки

void Blunk()
{
	// заполнение матрицы сетки
	for (int i = 0; i < celln; i++)
	{
		for (int j = 0; j < celln; j++)
		{
			field[i][j] = 0;
		}
	}
}

void DrawPoint(int cx, int cy) {//функция отрисовки круга в клеточке

	SelectObject(dc, brush_point);
	SelectObject(dc, pen_point);

	Ellipse(dc, (cx - 1) * cells + cx, shift + (celln - cy) * cells + celln - cy + 1, 
		cx * cells + cx, shift + (celln - cy + 1) * cells + celln - cy + 1);
	
	DeleteObject(brush_point);
	DeleteObject(pen_point);
}

void DrawNet() {//функция отрисовки сетки
	int x = 0, y = 0;//вспомогательные переменные

	//отрисовка вертикальных линий
	SelectObject(dc, pen_net);//выбор пера для сетки
	while (x <= celln) {
		MoveToEx(dc, x * cells + x, shift, 0);//перенос текущей позиции
		LineTo(dc, x * cells + x, shift + cells * celln + celln);//провести линию
		x++;
	}
	DeleteObject(pen_net);//освобождение памяти, псле использования пера

	//отрисовка горизонтальных линий
	SelectObject(dc, pen_net);//выбор пера для сетки
	while (y <= celln) {
		MoveToEx(dc, 0, shift + y * cells + y, 0);//перенос текущей позиции
		LineTo(dc, cells * celln + celln, shift + y * cells + y);//провести линию
		y++;
	}
	DeleteObject(pen_net);//освобождение памяти, после использования пера
}

void DrawHorLine(int x1, int x2, int y) 
{
	//вспомогательная функция для треугольника
	for (int i = x1; i <= x2; i++)
	{
		field[i][y] = colour;
	}

	//отрисовка границ треугольника по Y
	field[x1][y] = 1;
	field[x2][y] = 1;
}

void DrawTrian(int Ax, int Ay, int Bx, int By, int Cx, int Cy) {

	//функция заполнение массива для фигуры треугольник
	colour++;
	//сортировка вершин по убыванию Y
	int tmp;
	int X[3] = { Ax,Bx,Cx };
	int Y[3] = { Ay,By,Cy };
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			if (Y[j] < Y[j + 1])
			{
				tmp = Y[j + 1];
				Y[j + 1] = Y[j];
				Y[j] = tmp;
				tmp = X[j + 1];
				X[j + 1] = X[j];
				X[j] = tmp;
			}

	Cx = X[0]; Bx = X[1]; Ax = X[2];
	Cy = Y[0]; By = Y[1]; Ay = Y[2];

	int x1, x2;
	for (int sy = Ay; sy <= Cy; sy++)
	{

		x1 = Ax + (sy - Ay) * (Cx - Ax) / (Cy - Ay);
		if (sy < By) x2 = Ax + (sy - Ay) * (Bx - Ax) / (By - Ay);
		else
		{

			if (Cy == By) x2 = Bx;
			else
				x2 = Bx + (sy - By) * (Cx - Bx) / (Cy - By);
		}

		if (x1 > x2)
		{
			tmp = x1;
			x1 = x2;
			x2 = tmp;
		}
		DrawHorLine(x1, x2, sy + 1);//отрисова построчно
	}

	//отрисовка границ треугольника по X  
	for (int i = 0; i < celln; i++)
	{
		for (int j = 0; j < celln; j++)
		{
			if (field[i][j] == colour && field[i][j - 1] != colour)
			{
				field[i][j] = 1;
				j++;
			}
			if (field[i][j] == colour && field[i][j + 1] != colour)
				field[i][j + 1] = 1;
		}
	}
}

void LineBres(int x1, int y1, int x2, int y2, int c)
{
	//функция отрисовки линии по алгоритму Брезенхейма
	int dx = abs(x2 - x1), dy = abs(y2 - y1);//модули приращения по х и у 
	int sx, sy;//знаки приращения по х и у
	int e = dx - dy; //разница приращений

	if (x1 < x2) sx = 1;//определение знака приращения по х
	else sx = -1;

	if (y1 < y2) sy = 1;//определение знака приращения по у
	else sy = -1;

	field[x2][y2] = c;//отрисовка конца линии

	while (x1 != x2 || y1 != y2)
	{
		field[x1][y1] = c;//отрисовка текущей клетки

		if (e * 2 > -dy)
		{//преремещеие по х при отрисовке
			e -= dy;
			x1 += sx;
		}
		else
		{//перемещение по у при отрисовке
			e += dx;
			y1 += sy;
		}
	}
}

void CenterCircle(int x1, int y1, int R)
{
	//функция заполнения массива для фигуры окружность (заполнение внутренней части)
	colour++;
	
	int x, y;//координаты текущей точки
	int e, n;//вспомагательные переменные

	//начальные значения
	x = -R;
	y = 0;
	e = 2 - (2 * R);

	do {
		LineBres(x1, y1, x1 - x, y1 + y, colour);
		LineBres(x1, y1, x1 - y, y1 - x, colour);
		LineBres(x1, y1, x1 + x, y1 - y, colour);
		LineBres(x1, y1, x1 + y, y1 + x, colour);

		n = e;
		if (n > x) e += ++x * 2 + 1;
		if (n <= y) e += ++y * 2 + 1;
	} while (x < 0);
}

void Circle(int x1, int y1, int R)
{
	//функция заполнения массива для фигуры окружость (граница)
	CenterCircle(x1, y1, R);
	//алгоритм Брезенхема, окружность разделется на четыре части
	int x, y;//координаты текущей точки
	int e, n;//вспомагательные переменные

	//начальные значения
	x = -R;
	y = 0;
	e = 2 - (2 * R);

	do {
		//отрисовка четырех частей окружности

		field[x1 - x][y1 + y] = 1;
		field[x1 - y][y1 - x] = 1;
		field[x1 + x][y1 - y] = 1;
		field[x1 + y][y1 + x] = 1;

		n = e;
		if (n > x) e += ++x * 2 + 1;
		if (n <= y) e += ++y * 2 + 1;
	} while (x < 0);
}

void Сlick(int x, int y)
{
	//функция закрашивания выбранной области
	int c = field[x][y];

	for (int i = 0; i < celln; i++)
	{
		for (int j = 0; j < celln; j++)
		{

			if (field[i][j] == 1)
			{
				brush_point = CreateSolidBrush(RGB(153, 50, 204));
				DrawPoint(i, j);
			}

			if (field[i][j] == c)
			{
				brush_point = CreateSolidBrush(RGB(176 + 1 * field[i][j], 11 + 35 * field[i][j], 50 + 40 * field[i][j]));
				DrawPoint(i, j);
			}
		}
	}
}

void DrawAll()
{
	//функция отрисовки всего массива
	for (int i = 0; i < celln; i++)
	{
		for (int j = 0; j < celln; j++)
		{

			if (field[i][j] == 1)
			{
				brush_point = CreateSolidBrush(RGB(153, 50, 204));
				DrawPoint(i, j);
			}

			if (field[i][j] != 1 && field[i][j] != 0)
			{
				brush_point = CreateSolidBrush(RGB(176 + 1 * field[i][j], 11 + 35 * field[i][j], 50 + 40 * field[i][j]));
				DrawPoint(i, j);
			}
		}
	}
}


int main()
{
	Blunk(); // заполнение массива поля 
	DrawNet(); // отрисовка сетки

	Circle(40, 40, 30);
	DrawTrian(40, 20, 60, 50, 30, 60);
	Circle(20, 40, 10);

	//Сlick(20, 20);//выбор области для закрашивания
	DrawAll();//закрашивание всех фигур
}
#include <iostream>
#include <windowsx.h>
#include <windows.graphics.h>
#include <math.h>
using namespace std;
#define OO 250

struct dot
{
    int x;
    int y;
};


void DrawGrid(HDC* hdc);
void DrawDot(HDC hdc, int a, int b);

int sign(double x)
{
    if (x > 0) return 1;
    else if (x < 0) return -1;
    else return 0;
}

void Digital_something(HDC hdc,int x1,int y1,int x2,int y2)
{

    if (x1 < 1) x1 = 1;
    if (y1 < 1) y1 = 1;
    if (x1 > 10) x1 = 10;
    if (y1 > 10) y1 = 10;
    if (x2 < 1) x2 = 1;
    if (y2 < 1) y2 = 1;
    if (x2 > 10) x2 = 10;
    if (y2 > 10) y2 = 10;

    DrawDot(hdc, x2, y2);


    double Dx = 0, Dy = 0, d = 0;
    if (abs(x2 - x1) >= abs(y2 - y1) ? d = abs(x2 - x1) : d = abs(y2 - y1));
    Dx = (x2 - x1) / d;
    Dy = (y2 - y1) / d;
    double x = x1 + 0.5 * sign(Dx), y = y1 + 0.5 * sign(Dy);
    int i = 1;
    while (i <= d)
    {
        DrawDot(hdc, (int)x, (int)y);
        x = x + Dx;
        y = y + Dy;
        i++;
    }
}


void Brezenheim(HDC hdc,int x1,int y1,int x2,int y2)
{
    int dX = abs(x2 - x1);
    int dY = abs(y2 - y1);
    int signX = x1 < x2 ? 1 : -1;
    int signY = y1 < y2 ? 1 : -1;
    //
    int error = dX - dY;
    //
    DrawDot(hdc, x2, y2);
    while (x1 != x2 || y1 != y2)
    {
        DrawDot(hdc, x1, y1);
        int error2 = error * 2;
        if (error2 > -dY)
        {
            error -= dY;
            x1 += signX;
        }
        else
        {
            error += dX;
            y1 += signY;
        }
    }
}

void sorttreug(HDC hdc,int Ax, int Ay, int Bx, int By, int Cx, int Cy)
{
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
    Cy = Y[0]; By = Y[1]; Ay = Y[2];
    Cx = X[0]; Bx = X[1]; Ax = X[2];
    int x1, x2;
    for (int sy = Ay; sy < Cy-1; sy++)
    {
        x1 = Ax + (sy - Ay) * (Cx - Ax) / (Cy - Ay);
        if (sy < By)
            x2 = Ax + (sy - Ay) * (Bx - Ax) / (By - Ay);
        else
        {
            if (Cy == By)
                x2 = Bx;
            else
                x2 = Bx + (sy - By) * (Cx - Bx) / (Cy - By);
        }
        if (x1 > x2)
        {
            int tmp = x1;
            x1 = x2;
            x2 = tmp;
        }
        Digital_something(hdc,x1+1, sy+1 , x2+1, sy+1 );
    }
}

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "ru");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    POINT p;
    HWND hwnd = GetConsoleWindow();
    HDC hdc = GetDC(hwnd);
    HPEN whitePen = GetStockPen(WHITE_PEN);
    HBRUSH blackBrush = GetStockBrush(BLACK_BRUSH);
    HBRUSH yellowBrush = CreateSolidBrush(RGB(255, 255, 255));
    HBRUSH redBrush = CreateSolidBrush(RGB(255,0,0));
    SelectBrush(hdc, blackBrush);
    FloodFill(hdc, 0, 0, RGB(0, 0, 1));
    SelectBrush(hdc, yellowBrush);
    int Ax, Ay, Bx, By, Cx, Cy;
    cout << "Введите координаты точки A"<<endl;
    cin >> Ax >> Ay;
    cout << "Введите координаты точки B" << endl;
    cin >> Bx >> By;
    cout << "Введите координаты точки C" << endl;
    cin >> Cx >> Cy;
    Brezenheim(hdc, Ax, Ay, Bx, By);
    Brezenheim(hdc, Bx, By, Cx, Cy);
    Brezenheim(hdc, Ax, Ay, Cx, Cy);
    sorttreug(hdc, Ax, Ay, Bx, By, Cx, Cy);
    SelectPen(hdc, whitePen);
    DrawGrid(&hdc);
}

    

void DrawGrid(HDC* hdc)
{
    int x, y, x1, y1;
    x = y = x1 = y1 = OO;
    for (int i = 0; i <= 10; i++)
    {
        MoveToEx(*hdc, x, y, NULL);
        LineTo(*hdc, x + 300, y);
        y += 30;
    }
    for (int j = 0; j <= 10; j++)
    {
        MoveToEx(*hdc, x1, y1, NULL);
        LineTo(*hdc, x1, y1 + 300);
        x1 += 30;
    }

}

void DrawDot(HDC hdc, int a, int b) {

    int x, y;
    x = (OO + 15) + 30 * (a - 1);
    y = (OO + 15) + 30 * (b - 1);
    Ellipse(hdc, x - 15, y + 15, x + 15, y - 15);
}

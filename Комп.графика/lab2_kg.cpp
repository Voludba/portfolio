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

int sign(double x)
{
    if (x > 0) return 1;
    else if (x < 0) return -1;
    else return 0;
}

void DrawGrid(HDC* hdc);
void DrawDot(HDC hdc, int a, int b);

void Digital_something(HDC hdc)
{
    int x1, y1, x2, y2;
    cout << "Enter the coords of start dot (on 10x10 grid)";
    cin >> x1 >> y1;
    cout << "Enter the coords of finish dot (on 10x10 grid)";
    cin >> x2 >> y2;

    if (x1 < 1) x1 = 1;
    if (y1 < 1) y1 = 1;
    if (x1 > 10) x1 = 10;
    if (y1 > 10) y1 = 10;
    if (x2 < 1) x2 = 1;
    if (y2 < 1) y2 = 1;
    if (x2 > 10) x2 = 10;
    if (y2 > 10) y2 = 10;

    DrawDot(hdc, x2, y2);


    double Dx = 0, Dy = 0,d = 0;
    if (abs(x2 - x1) >= abs(y2 - y1) ? d = abs(x2 - x1): d = abs(y2 - y1));
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



void Brezenheim(HDC hdc)
{
    int x1, y1, x2, y2;
    cout << "Enter the coords of start dot (on 10x10 grid)";
    cin >> x1 >> y1;
    cout << "Enter the coords of finish dot (on 10x10 grid)";
    cin >> x2 >> y2;
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

void plot_circle(HDC hdc,int x, int y, int x_center, int  y_center)
{
    DrawDot(hdc,x_center + x, y_center + y);
    DrawDot(hdc,x_center + x, y_center - y);
    DrawDot(hdc,x_center - x, y_center + y);
    DrawDot(hdc,x_center - x, y_center - y);
}

void Circle(HDC hdc, int x_center, int y_center, int radius)
{
    int x, y, delta;
    x = 0;
    y = radius;
    delta = 3 - 2 * radius;
    while (x < y) {
        plot_circle(hdc,x, y, x_center, y_center);
        plot_circle(hdc,y, x, x_center, y_center);
        if (delta < 0)
            delta += 4 * x + 6;
        else {
            delta += 4 * (x - y) + 10;
            y--;
        }
        x++;
    }

    if (x == y) plot_circle(hdc,x, y, x_center, y_center);
}


int main(int argc, char* argv[])
{
    POINT p;
    HWND hwnd = GetConsoleWindow();
    HDC hdc = GetDC(hwnd);
    HPEN whitePen = GetStockPen(WHITE_PEN);
    HBRUSH blackBrush = GetStockBrush(BLACK_BRUSH);
    HBRUSH yellowBrush = CreateSolidBrush(RGB(255, 255, 255));
    SelectBrush(hdc, blackBrush);
    FloodFill(hdc, 0, 0, RGB(0, 0, 1));
    SelectBrush(hdc, yellowBrush);


    cout << "choose your way - Line(1) or Circle(2): ";
    int choice1 = 0;
    cin >> choice1;

    if (choice1 == 1)
    {
        cout << "Brezenheim(1) or Digital...(2): ";
        int choice2 = 0;
        cin >> choice2;
        if (choice2 == 1)
        {
            Brezenheim(hdc);
        }
        else if (choice2 == 2)
        {
            Digital_something(hdc);
        }
        else
        {
            cout << "Nepravilno";
        }
        
    }
    else if (choice1 == 2)
    {
        int x_center, y_center, r;
        cout << "Enter the coords of center (on 10x10 grid)";
        cin >> x_center >> y_center;
        cout << "Enter the raduis (on 10x10 grid)";
        cin >> r;
        Circle(hdc, x_center, y_center, r);
    }
    else
    {
        cout << "Nepravilno";
    }
    SelectPen(hdc, whitePen);
    DrawGrid(&hdc);

    ReleaseDC(hwnd, hdc);
    return 0;
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
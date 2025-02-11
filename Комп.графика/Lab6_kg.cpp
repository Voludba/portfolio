#include <iostream>
#include "glut.h"


float points[100][100];

const int window_side_size = 600; //размер окна
const int view_side_size = 25; // масштаб сетки
const int period = 100; // скорость закрашивания

struct color_t
{
    double r, g, b, a;
    void setThis() const {
        const color_t& color = *this;
        glColor4d(color.r, color.g, color.b, color.a);
    }
};

const color_t black = { 0, 0, 0, 1 };
const color_t green = { 1, 0, 0, 1 };//красный
const color_t red = { 0, 0, 1, 1 };// сииний
const color_t white = { 0, 0, 0, 0 };// закрашивание клеток, не вошедших в фигуру

void DrawFatPixel(int x, int y, color_t color = black) // закрашивание клетки
{
    color.setThis();
    glBegin(GL_POLYGON);
    glVertex2d(x - 0.5, y - 0.5);
    glVertex2d(x - 0.5, y + 0.5);
    glVertex2d(x + 0.5, y + 0.5);
    glVertex2d(x + 0.5, y - 0.5);
    glEnd();
}

void DrawCell() // сетка
{
    glLineWidth(1);
    black.setThis();

    for (int i = -view_side_size; i <= view_side_size; ++i) {
        glBegin(GL_LINES);
        glVertex2f(i + 0.5f, -view_side_size + .0f);
        glVertex2f(i + 0.5f, view_side_size + .0f);
        glVertex2f(-view_side_size + .0f, i + 0.5f);
        glVertex2f(view_side_size + .0f, i + 0.5f);
        glEnd();
    }
}

void DrawAxes() { // оси x и y
    glLineWidth(2);
    red.setThis();
    glBegin(GL_LINES);
    glVertex2f(-50, 0.5);
    glVertex2f(50, 0.5);
    glVertex2f(0.5, -50);
    glVertex2f(0.5, 50);
    glEnd();
}

void DrawBrezenhemLine(int x1, int x2, int y1, int y2, color_t color = red) {
    int error = 0, lasty = -50, x = x1, y = y1;
    int px = abs(x2 - x1);
    int py = abs(y2 - y1);
    int deltaerr = (px >= py) ? py : px; // какое больше приращение, то и берём

    while (((x2 >= x1 && x <= x2) || (x2 < x1 && x >= x2)) && // пока не дошли по х и у от первой точки до второй
        ((y2 >= y1 && y <= y2) || (y2 < y1 && y >= y2))) {

        for (int a = x + 30; a < 50; a++) {
            if (a > x + 30) {

                if (lasty == y)
                    break;

                if (x2 < x1 && y2 < y1 && y == y1) // если ребро параллельное оси Х
                    break;

                if (points[a][y + 30] == 1) points[a][y + 30] = 0;
                else  points[a][y + 30] = 1; // заполнение двумерного массива (1 или 0)
            }
        }

        lasty = y;
        DrawFatPixel(x, y, color);
        error = error + deltaerr;

        if (px >= py) {
            if (2 * error >= deltaerr) {
                if (y2 < y1) y--;
                else y++;
                error = error - px;
            }
            if (x2 > x1) x++;
            else if (x2 < x1) x--;
        }
        else {
            if (2 * error >= deltaerr) {
                if (x2 > x1) x++;
                else if (x2 < x1) x--;
                error = error - py;
            }
            if (y2 > y1) y++;
            else if (y2 < y1) y--;
        }
    }
}

void DrawPolygon(const int tick) { // построчное закрашивание фигуры и фона
    for (int y = 0; y < 100 && y < tick; y++) {
        for (int x = 0; x < 100; x++) {
            if (points[x][y] == 1)
                DrawFatPixel(x - 30, y - 30, green);
            else DrawFatPixel(x - 30, y - 30, white);
        }
    }
}

void Display() {
    glClear(GL_COLOR_BUFFER_BIT);

    int x1 = -20, y1 = -15,
        x2 = -10, y2 = 15,
        x3 = 0, y3 = 5,
        x4 = 15, y4 = 15,
        x5 = 20, y5 = 0,
        x6 = 14, y6 = -20;
    static int tick = 0;
    tick++;
    DrawBrezenhemLine(x1, x2, y1, y2);
    DrawBrezenhemLine(x2, x3, y2, y3);
    DrawBrezenhemLine(x3, x4, y3, y4);
    DrawBrezenhemLine(x4, x5, y4, y5);
    DrawBrezenhemLine(x5, x6, y5, y6);
    DrawBrezenhemLine(x6, x1, y6, y1 - 1);
    DrawPolygon(tick);
    DrawBrezenhemLine(x1, x2, y1, y2, red);
    DrawBrezenhemLine(x2, x3, y2, y3, red);
    DrawBrezenhemLine(x3, x4, y3, y4, red);
    DrawBrezenhemLine(x4, x5, y4, y5, red);
    DrawBrezenhemLine(x5, x6, y5, y6, red);
    DrawBrezenhemLine(x6, x1, y6, y1 - 1, red);
    DrawAxes();
    DrawCell();

    glFlush();
}

void timf(int value) {
    glutPostRedisplay();
    glutTimerFunc(period, timf, 0);
}

void Initialize() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-view_side_size, view_side_size, -view_side_size, view_side_size, -1.0, 1.0);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv); // главная иницилизирующая функция
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // установка одинарного буфера и цветовой модели RGB
    glutInitWindowSize(window_side_size, window_side_size);
    glutInitWindowPosition(300, 100); // позиция окна
    glutCreateWindow("Савин В., Кузнецов Н., Авт-010"); // создание окна
    glutTimerFunc(period, timf, 0); // функция таймера
    glutDisplayFunc(Display); // функция отображения (рисования)
    Initialize(); // инициализация
    glutMainLoop(); // обработка событий GLUT, бесконечный цикл
    return 0;
}
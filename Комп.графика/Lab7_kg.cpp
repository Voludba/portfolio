// ConsoleApplication3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <windows.h>
#include <locale.h>
#include <gl/GLU.h>
#include <gl/GL.h>
#include <glut.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdio.h>
GLfloat xrot, vxrot = 1.0; // X вращение
GLfloat yrot, vyrot = 1.0; // Y вращение
GLfloat zrot, vzrot = 1.0; // Z вращение
GLint a = 15;  // размер куба
GLint xxx = 0, yyy = 0, zzz = 0; //смещение

void display()
{
	glClear(GL_COLOR_BUFFER_BIT); // перерисовка
	glLineWidth(7);//Ширина линии
	glColor3f(0, 0, 0);//черный
	glBegin(GL_LINE_STRIP); // рисуем одну сторону куба
	glVertex3f(0, 0, 0);
	glVertex3f(70, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 70, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(-50, -50, 0);
	glVertex3f(0, 0, 0);
	glEnd();
	glPushMatrix(); // конструкция для сохранения положения осей.
	glTranslatef(xxx, yyy, zzz);
	glRotatef(xrot, 1, 0, 0); // Вращение по оси X на xrot
	glRotatef(yrot, 0, 1, 0); // Вращение по оси Y по yrot
	glRotatef(zrot, 0, 0, 1); // Вращение по оси Z по zrot
	glLineWidth(3);//Ширина линии
	glColor3f(0, 1, 0);//Зелёный
	glBegin(GL_LINE_STRIP); // рисуем одну сторону куба
	glVertex3f(-a, -a, -a);
	glVertex3f(a, -a, -a);
	glVertex3f(a, a, -a);
	glVertex3f(-a, a, -a);
	glVertex3f(-a, -a, -a);
	glEnd();
	glLineWidth(3);//Ширина линии
	glColor3f(1, 0, 0);//красный
	glBegin(GL_LINE_STRIP); // вторая сторона куба
	glVertex3f(-a, -a, a);
	glVertex3f(a, -a, a);
	glVertex3f(a, a, a);
	glVertex3f(-a, a, a);
	glVertex3f(-a, -a, a);
	glEnd();
	glLineWidth(3);//Ширина линии
	glColor3f(0, 0, 1);//синий
	glBegin(GL_LINES); // соеденяем углы соответсвующие линиями
	glVertex3f(-a, -a, a);
	glVertex3f(-a, -a, -a);
	glVertex3f(a, -a, a);
	glVertex3f(a, -a, -a);
	glLineWidth(3);//Ширина линии
	glColor3f(0, 1, 1);//голубой
	glVertex3f(a, a, a);
	glVertex3f(a, a, -a);
	glVertex3f(-a, a, a);
	glVertex3f(-a, a, -a);
	glEnd();
	glPopMatrix();
	glutSwapBuffers();
}
void timer(int = 0) // таймер на вращение куба
{
	display(); // вызов функции прорисовки куб
	glutTimerFunc(10, timer, 0); // таймер на 10 милисекунд
}
void SKeyboard(int key, int x, int y) // функция обработки кливиатуры
{
	switch (key)
	{
	case GLUT_KEY_F1: a += 1; // увеличение куба
		break;
	case GLUT_KEY_F2: a -= 1; // уменьшение куба
		break;
	case GLUT_KEY_F3: xxx += 1; // смещение по х с +
		break;
	case GLUT_KEY_F4: xxx -= 1; // смещение по х с -
		break;
	case GLUT_KEY_F5: yyy += 1; // смещение по y с +
		break;
	case GLUT_KEY_F6: yyy -= 1; // смещение по y с -
		break;
	case GLUT_KEY_F7: zzz += 1; // смещение по z с +
		break;
	case GLUT_KEY_F8: zzz -= 1; // смещение по z с -
		break;
	case GLUT_KEY_LEFT: yrot += vyrot; // движение по y
		break;
	case GLUT_KEY_RIGHT: yrot -= vyrot; // движение по y
		break;
	case GLUT_KEY_UP: xrot += vxrot; //движение по х
		break;
	case GLUT_KEY_DOWN: xrot -= vxrot; // движение по х
		break;
	case GLUT_KEY_PAGE_UP: zrot += vzrot; // движение по z
		break;
	case GLUT_KEY_PAGE_DOWN: zrot -= vzrot; // движение по z
		break;
	case GLUT_KEY_F12: exit(1); // выход из программы
		break;

	}
}

int main(int argc, char** argv) // главная функция

{
	setlocale(LC_ALL, "russian"); // подключение русской локализации
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400); // задаем размер окна
	glutInitWindowPosition(400, 200); // задаем положение окна
	glutCreateWindow("Cube Шипицына, Рахимова, Молчков"); // заголовок окна
	glClearColor(1, 1, 1, 1.0); // задаем черный цвет
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); // считывает текущую матрицу
	glOrtho(-100, 100, -100, 100, -100, 100); //cоздаем пространство нашей сцены
	glutSpecialFunc(SKeyboard); // регистрация "нажатие клавиш"
	//glutKeyboardFunc(SKeyboard);
	glutDisplayFunc(display); // регистрация "рисование куба"
	timer(); // регистрация таймера
	glutMainLoop(); // бесконечный цикл

}


// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.

#include <windows.h>
#include <locale.h>
#include <gl/GLU.h>
#include <gl/GL.h>
#include <glut.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdio.h>

float xrot, vxrot = 1.0; // X вращение
float yrot, vyrot = 1.0; // Y вращение
float zrot, vzrot = 1.0; // Z вращение
int a = 10;  // Размер куба
float xxx = 0, yyy = 0; // Смещение

void display() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    glOrtho(-100, 100, -100, 100, -100, 100);
    // Оси x, y, z
    glLineWidth(7);
    glColor3f(0, 0, 0);
    glBegin(GL_LINE_STRIP);
    glVertex3f(0, 0, 0);
    glVertex3f(70, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 70, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(-50, -50, 0);
    glVertex3f(0, 0, 0);
    glEnd();
    glPushMatrix();
    glTranslatef(xxx, yyy, 0);

    glRotatef(xrot, 1, 0, 0); // Вращение по оси X на xrot
    glRotatef(yrot, 0, 1, 0); // Вращение по оси Y по yrot
    glRotatef(zrot, 0, 0, 1); // Вращение по оси Z по zrot


    glBegin(GL_POLYGON);
    // Задняя сторона
    glColor3f(0.0, 1.0, 0.0);     glVertex3f(a, -a, -a);
    glColor3f(1.0, 0.0, 1.0);     glVertex3f(a, a, -a);
    glColor3f(1.0, 0.0, 0.0);     glVertex3f(-a, a, -a);
    glColor3f(0.0, 0.0, 1.0);     glVertex3f(-a, -a, -a);

    glEnd();
    // Передняя сторона
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 0.0);   glVertex3f(a, -a, a);
    glColor3f(0.0, 0.0, 1.0);   glVertex3f(a, a, a);
    glColor3f(0.0, 1.0, 0.0);   glVertex3f(-a, a, a);
    glColor3f(1.0, 0.0, 1.0);   glVertex3f(-a, -a, a);
    glEnd();
    // Правая сторона
    glBegin(GL_POLYGON);
    glColor3f(0.0, 1.0, 0.0);   glVertex3f(a, -a, -a);
    glColor3f(1.0, 0.0, 1.0);   glVertex3f(a, a, -a);
    glColor3f(0.0, 0.0, 1.0);   glVertex3f(a, a, a);
    glColor3f(1.0, 0.0, 0.0);   glVertex3f(a, -a, a);
    glEnd();
    // Левая сторона
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 1.0);   glVertex3f(-a, -a, a);
    glColor3f(0.0, 1.0, 0.0);   glVertex3f(-a, a, a);
    glColor3f(1.0, 0.0, 0.0);   glVertex3f(-a, a, -a);
    glColor3f(0.0, 0.0, 1.0);   glVertex3f(-a, -a, -a);
    glEnd();
    // Верхняя сторона
    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.0, 1.0);   glVertex3f(a, a, a);
    glColor3f(1.0, 0.0, 1.0);   glVertex3f(a, a, -a);
    glColor3f(1.0, 0.0, 0.0);   glVertex3f(-a, a, -a);
    glColor3f(0.0, 1.0, 0.0);   glVertex3f(-a, a, a);
    glEnd();
    // Нижняя сторона
    glBegin(GL_POLYGON);
    glColor3f(0.0, 1.0, 0.0);   glVertex3f(a, -a, -a);
    glColor3f(1.0, 0.0, 0.0);   glVertex3f(a, -a, a);
    glColor3f(1.0, 0.0, 1.0);   glVertex3f(-a, -a, a);
    glColor3f(0.0, 0.0, 1.0);   glVertex3f(-a, -a, -a);
    glEnd();

    glFlush();
    glutSwapBuffers();

}

void specialKeys(int key, int x, int y) {
    {
        switch (key)
        {
        case GLUT_KEY_F1: a += 1; // Увеличение куба
            break;
        case GLUT_KEY_F2: a -= 1; // Уменьшение куба
            break;
        case GLUT_KEY_F3: xxx += 1; // Смещение по х с +
            break;
        case GLUT_KEY_F4: xxx -= 1; // Смещение по х с -
            break;
        case GLUT_KEY_F5: yyy += 1; // Смещение по y с +
            break;
        case GLUT_KEY_F6: yyy -= 1; // Смещение по y с -
            break;
        case GLUT_KEY_F7: xxx -= 0.7, yyy -= 0.7; // Смещение по z с +
            break;
        case GLUT_KEY_F8: xxx += 0.7, yyy += 0.7; // Смещение по z с -
            break;
        case GLUT_KEY_LEFT: yrot += vyrot; // Движение по y
            break;
        case GLUT_KEY_RIGHT: yrot -= vyrot; // Движение по y
            break;
        case GLUT_KEY_UP: xrot += vxrot; // Движение по х
            break;
        case GLUT_KEY_DOWN: xrot -= vxrot; // Движение по х
            break;
        case GLUT_KEY_PAGE_UP: zrot += vzrot; // Движение по z
            break;
        case GLUT_KEY_PAGE_DOWN: zrot -= vzrot; // Движение по z
            break;
        case GLUT_KEY_F12: exit(1); // Выход из программы
            break;
        }

        glutPostRedisplay();

    };
}

int main(int argc, char* argv[]) {

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(800, 800);
    glutInitWindowPosition(510, 90);

    glutCreateWindow("Куб(не фильм)");
    glClearColor(1, 1, 1, 1.0);

    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
    glutSpecialFunc(specialKeys);

    glutMainLoop();

    return 0;

}
#include <cmath>
#include <iostream>

#include "functions.hpp"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_LINE_SMOOTH);
}

void drawLattice() {
    glColor3d(0.2, 0.2, 0.2);
    glBegin(GL_LINES);
    glVertex2d(-1.0, 0.0);
    glVertex2d(1.0, 0.0);
    glVertex2d(0.0, -1.0);
    glVertex2d(0.0, 1.0);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();

    drawLattice();

    glBegin(GL_LINES);

    glColor3d(1, 1, 1);
    glVertex2d(0.0, 0.0);
    glVertex2d(0.5, -0.5);

    glEnd();

    glutSwapBuffers();
}

void centreViewport(int width, int height) {
    int window_size = std::min(width, height);

    int x0 = (width - window_size) / 2;
    int y0 = (height - window_size) / 2;

    glViewport(x0, y0, window_size, window_size);
}

void reshape(int width, int height) {
    centreViewport(width, height);

    glLoadIdentity();
    gluPerspective(30.0, (double)width / (double)height, 1.0, 100.0);
    glTranslated(0.0, 0.0, -5.0);
    gluLookAt(3.0, 4.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

    glutCreateWindow(argv[0]);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    init();

    glutMainLoop();

    return 0;
}
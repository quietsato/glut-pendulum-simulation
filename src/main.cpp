#include <cmath>
#include <iostream>

#include "functions.hpp"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

double g = 9.8;
double m1 = 1.0;
double l1 = 0.5;

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

double h = 0.1;

double theta1 = M_PI / 3;
double omega1 = 0;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();

    drawLattice();

    glBegin(GL_LINES);

    glColor3d(1, 1, 1);

    // runge-kutta
    double k1_theta1 = h * theta_dot1(omega1);
    double k1_omega1 = h * omega_dot1(g, m1, 0, l1, 0, theta1, 0, 0, 0);

    double k2_theta1 = h * theta_dot1(omega1 + k1_omega1 / 2);
    double k2_omega1 =
        h * omega_dot1(g, m1, 0, l1, 0, theta1 + k1_theta1 / 2, 0, 0, 0);

    double k3_theta1 = h * theta_dot1(omega1 + k2_omega1 / 2);
    double k3_omega1 =
        h * omega_dot1(g, m1, 0, l1, 0, theta1 + k2_theta1 / 2, 0, 0, 0);

    double k4_theta1 = h * theta_dot1(omega1 + k3_omega1);
    double k4_omega1 =
        h * omega_dot1(g, m1, 0, l1, 0, theta1 + k3_theta1, 0, 0, 0);

    theta1 += (k1_theta1 + 2 * k2_theta1 + 2 * k3_theta1 + k4_theta1) / 6;

    glVertex2d(0.0, 0.0);
    glVertex2d(l1 * cos(theta1), -l1 * sin(theta1));

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

void idle() { glutPostRedisplay(); }

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

    glutCreateWindow(argv[0]);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);

    init();

    glutMainLoop();

    return 0;
}
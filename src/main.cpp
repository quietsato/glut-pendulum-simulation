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
double m2 = 1.0;
double l2 = 0.2;

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

double h = 0.001;

double theta1 = M_PI / 6;
double omega1 = 0;
double theta2 = M_PI / 3;
double omega2 = 0;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();

    drawLattice();

    // runge-kutta
    double k1_theta1 = h * theta_dot1(omega1);
    double k1_theta2 = h * theta_dot2(omega2);
    double k1_omega_dot1 =
        omega_dot1(g, m1, m2, l1, l2, theta1, theta2, omega2);
    double k1_omega_dot2 =
        omega_dot2(g, m1, m2, l1, l2, theta1, theta2, k1_omega_dot1);
    double k1_omega1 = h * k1_omega_dot1;
    double k1_omega2 = h * k1_omega_dot2;

    double k2_theta1 = h * theta_dot1(omega1 + k1_omega1 / 2);
    double k2_theta2 = h * theta_dot2(omega2 + k1_omega2 / 2);
    double k2_omega_dot1 =
        omega_dot1(g, m1, m2, l1, l2, theta1 + k1_theta1 / 2,
                   theta2 + k1_theta2 / 2, omega2 + k1_omega2 / 2);
    double k2_omega_dot2 = omega_dot2(g, m1, m2, l1, l2, theta1 + k1_theta1 / 2,
                                      theta2 + k1_theta2 / 2, k2_omega_dot1);
    double k2_omega1 = h * k2_omega_dot1;
    double k2_omega2 = h * k2_omega_dot2;

    double k3_theta1 = h * theta_dot1(omega1 + k2_omega1 / 2);
    double k3_theta2 = h * theta_dot2(omega2 + k2_omega2 / 2);
    double k3_omega_dot1 =
        omega_dot1(g, m1, m2, l1, l2, theta1 + k2_theta1 / 2,
                   theta2 + k2_theta2 / 2, omega2 + k2_omega2 / 2);
    double k3_omega_dot2 = omega_dot2(g, m1, m2, l1, l2, theta1 + k2_theta1 / 2,
                                      theta2 + k2_theta2 / 2, k3_omega_dot1);
    double k3_omega1 = h * k3_omega_dot1;
    double k3_omega2 = h * k3_omega_dot2;

    double k4_theta1 = h * theta_dot1(omega1 + k3_omega1);
    double k4_theta2 = h * theta_dot2(omega2 + k3_omega2);
    double k4_omega_dot1 = omega_dot1(g, m1, m2, l1, l2, theta1 + k3_theta1,
                                      theta2 + k3_theta2, omega2 + k3_omega2);
    double k4_omega_dot2 = omega_dot2(g, m1, m2, l1, l2, theta1 + k3_theta1,
                                      theta2 + k3_theta2, k4_omega_dot1);
    double k4_omega1 = h * k4_omega_dot1;
    double k4_omega2 = h * k4_omega_dot2;

    theta1 += (k1_theta1 + 2 * k2_theta1 + 2 * k3_theta1 + k4_theta1) / 6.0;
    omega1 += (k1_omega1 + 2 * k2_omega1 + 2 * k3_omega1 + k4_omega1) / 6.0;
    theta2 += (k1_theta2 + 2 * k2_theta2 + 2 * k3_theta2 + k4_theta2) / 6.0;
    omega2 += (k1_omega2 + 2 * k2_omega2 + 2 * k3_omega2 + k4_omega2) / 6.0;

    glBegin(GL_LINES);

    glColor3d(1, 1, 1);

    glVertex2d(0.0, 0.0);
    glVertex2d(l1 * sin(theta1), -l1 * cos(theta1));
    glVertex2d(l1 * sin(theta1), -l1 * cos(theta1));
    glVertex2d(l1 * sin(theta1) + l2 * sin(theta2),
               -l1 * cos(theta1) - l2 * sin(theta2));

    glEnd();

    // printf("%lf %lf\n", theta1, theta2);

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
}

void idle() { glutPostRedisplay(); }

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            glutIdleFunc(idle);
        }
        else if (state == GLUT_UP) {
            glutIdleFunc(0);
        }
    }
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

    glutCreateWindow(argv[0]);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    // glutIdleFunc(idle);

    init();

    glutMainLoop();

    return 0;
}
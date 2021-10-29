#include <cmath>
#include <iostream>
#include <vector>

#include "functions.hpp"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define INF 1000000
#define HISTORY_MAX 1000

double g = 9.8;
double m1 = 1.0;
double l1 = 0.5;
double m2 = 0.5;
double l2 = 0.25;

std::vector<std::pair<double, double>> history;
size_t history_index = 0;

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

double h = 0.005;

double theta1 = 2 * M_PI / 3;
double omega1 = 0;
double theta2 = 2 * M_PI / 3;
double omega2 = 0;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();

    drawLattice();

    // runge-kutta
    double k1_theta1 = h * theta_dot1(omega1);
    double k1_theta2 = h * theta_dot2(omega2);
    double k1_omega_dot1 =
        omega_dot1(g, m1, m2, l1, l2, theta1, theta2, omega1, omega2);
    double k1_omega_dot2 =
        omega_dot2(g, m1, m2, l1, l2, theta1, theta2, omega1, omega2);
    double k1_omega1 = h * k1_omega_dot1;
    double k1_omega2 = h * k1_omega_dot2;

    double k2_theta1 = h * theta_dot1(omega1 + k1_omega1 / 2);
    double k2_theta2 = h * theta_dot2(omega2 + k1_omega2 / 2);
    double k2_omega_dot1 = omega_dot1(
        g, m1, m2, l1, l2, theta1 + k1_theta1 / 2, theta2 + k1_theta2 / 2,
        omega1 + k1_omega1 / 2, omega2 + k1_omega2 / 2);
    double k2_omega_dot2 = omega_dot2(
        g, m1, m2, l1, l2, theta1 + k1_theta1 / 2, theta2 + k1_theta2 / 2,
        omega1 + k1_omega1 / 2, omega2 + k1_omega2 / 2);
    double k2_omega1 = h * k2_omega_dot1;
    double k2_omega2 = h * k2_omega_dot2;

    double k3_theta1 = h * theta_dot1(omega1 + k2_omega1 / 2);
    double k3_theta2 = h * theta_dot2(omega2 + k2_omega2 / 2);
    double k3_omega_dot1 = omega_dot1(
        g, m1, m2, l1, l2, theta1 + k2_theta1 / 2, theta2 + k2_theta2 / 2,
        omega1 + k2_omega1 / 2, omega2 + k2_omega2 / 2);
    double k3_omega_dot2 = omega_dot2(
        g, m1, m2, l1, l2, theta1 + k2_theta1 / 2, theta2 + k2_theta2 / 2,
        omega1 + k2_omega1 / 2, omega2 + k2_omega2 / 2);
    double k3_omega1 = h * k3_omega_dot1;
    double k3_omega2 = h * k3_omega_dot2;

    double k4_theta1 = h * theta_dot1(omega1 + k3_omega1);
    double k4_theta2 = h * theta_dot2(omega2 + k3_omega2);
    double k4_omega_dot1 =
        omega_dot1(g, m1, m2, l1, l2, theta1 + k3_theta1, theta2 + k3_theta2,
                   omega1 + k3_omega1, omega2 + k3_omega2);
    double k4_omega_dot2 =
        omega_dot2(g, m1, m2, l1, l2, theta1 + k3_theta1, theta2 + k3_theta2,
                   omega1 + k3_omega1, omega2 + k3_omega2);
    double k4_omega1 = h * k4_omega_dot1;
    double k4_omega2 = h * k4_omega_dot2;

    theta1 += (k1_theta1 + 2 * k2_theta1 + 2 * k3_theta1 + k4_theta1) / 6.0;
    omega1 += (k1_omega1 + 2 * k2_omega1 + 2 * k3_omega1 + k4_omega1) / 6.0;
    theta2 += (k1_theta2 + 2 * k2_theta2 + 2 * k3_theta2 + k4_theta2) / 6.0;
    omega2 += (k1_omega2 + 2 * k2_omega2 + 2 * k3_omega2 + k4_omega2) / 6.0;

    double x1 = l1 * sin(theta1), y1 = -l1 * cos(theta1);
    double x2 = x1 + l2 * sin(theta2), y2 = y1 - l2 * cos(theta2);

    glBegin(GL_LINES);

    glColor3d(1, 1, 1);

    glVertex2d(0.0, 0.0);
    glVertex2d(x1, y1);
    glVertex2d(x1, y1);
    glVertex2d(x2, y2);

    glEnd();

    if (history.size() < HISTORY_MAX) {
        history.push_back(std::pair<double, double>(x2, y2));

        glBegin(GL_LINES);
        glColor3d(1, 0, 0);
        for (size_t i = 0; i < history.size() - 1; i++) {
            glVertex2d(history[i].first, history[i].second);
            glVertex2d(history[i + 1].first, history[i + 1].second);
        }
        glEnd();
    } else {
        history[history_index] = std::pair<double, double>(x2, y2);

        glBegin(GL_LINES);
        glColor3d(1, 0, 0);
        for (size_t j = 0; j < HISTORY_MAX - 1; j++) {
            size_t i1 = (history_index + j + 1) % HISTORY_MAX;
            size_t i2 = (i1 + 1) % HISTORY_MAX;
            glVertex2d(history[i1].first, history[i1].second);
            glVertex2d(history[i2].first, history[i2].second);
        }
        glEnd();

        history_index = (history_index + 1) % HISTORY_MAX;
    }

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
        } else if (state == GLUT_UP) {
            glutIdleFunc(0);
        }
    }
}

void startupTimeout(int _value) {
    glutIdleFunc(idle);
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

    glutCreateWindow(argv[0]);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);

    glutTimerFunc(5000, startupTimeout, 0);

    init();

    glutMainLoop();

    return 0;
}
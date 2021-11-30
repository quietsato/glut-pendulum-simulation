#include <cmath>
#include <iostream>
#include <vector>

#include "pendulum/pendulum.hpp"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

std::vector<DoublePendulum *> p;
bool isEnableLocus = true;

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_LINE_SMOOTH);

    for (size_t i = 1; i < 7; i++) {
        auto pi = new DoublePendulum(              //
            /* m1 = */ 1.0, /* m2 = */ 0.1,        //
            /* l1 = */ 0.5, /* l2 = */ 0.5,        //
            /* theta1 = */ M_PI + (i * 0.0000001), //
            /* theta2 = */ M_PI,                   //
            /* omega1 = */ 0, /* omega2 = */ 0     //
        );
        pi->setLocusColor((i >> 2) & 1, (i >> 1) & 1, i & 1);
        p.push_back(pi);
    }
}

//
// Display
//
void drawLattice() {
    glColor3d(0.2, 0.2, 0.2);
    glBegin(GL_LINES);
    glVertex2d(-1.0, 0.0);
    glVertex2d(1.0, 0.0);
    glVertex2d(0.0, -1.0);
    glVertex2d(0.0, 1.0);
    glEnd();
}

void drawPendulum() {
    for (auto pi : p) {
        pi->step();
    }
    if (isEnableLocus) {
        for (auto pi : p) {
            pi->displayLocus();
        }
    }
    for (auto pi : p) {
        pi->displayPendulum();
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    drawLattice();
    drawPendulum();

    glutSwapBuffers();
}

void reshape(int width, int height) {
    // Center viewport
    {
        int window_size = std::min(width, height);

        int x0 = (width - window_size) / 2;
        int y0 = (height - window_size) / 2;

        glViewport(x0, y0, window_size, window_size);
    }
    glLoadIdentity();
}

void idle() { glutPostRedisplay(); }

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        isEnableLocus = !isEnableLocus;
    } else if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP) {
        for (auto pi : p) {
            pi->clearLocus();
        }
    }
}

void startupTimeout(int _value) { glutIdleFunc(idle); }

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
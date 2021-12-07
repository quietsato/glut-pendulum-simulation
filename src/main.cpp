#include <cmath>
#include <iostream>
#include <vector>

#include "config_loader/config_loader.hpp"
#include "pendulum/pendulum.hpp"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

std::vector<DoublePendulum *> p;
bool isEnableLocus = true;

void init(std::vector<PendulumConfig> config) {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_LINE_SMOOTH);

    for (PendulumConfig c : config) {
        auto pi = new DoublePendulum(                                 //
            c.m1, c.m2, c.l1, c.l2,                                   //
            c.theta1_deg / 180.0 * M_PI, c.theta2_deg / 180.0 * M_PI, //
            c.omega1_deg / 180.0 * M_PI, c.omega2_deg / 180.0 * M_PI  //
        );
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
    if (argc < 2) {
        std::cerr << "Please specify a config file path" << std::endl;
        exit(1);
    }
    std::vector<PendulumConfig> config = config_loader::load(argv[1]);

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

    glutCreateWindow(argv[0]);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);

    glutTimerFunc(5000, startupTimeout, 0);

    init(config);

    glutMainLoop();

    return 0;
}
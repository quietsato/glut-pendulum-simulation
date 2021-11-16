#include <cmath>
#include <iostream>
#include <vector>

#include "pendulum/pendulum.hpp"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

DoublePendulum *p1;
DoublePendulum *p2;
DoublePendulum *p3;
DoublePendulum *p4;

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_LINE_SMOOTH);

    p1 = new DoublePendulum(                                      //
        /* m1 = */ 1.0, /* m2 = */ 0.5,                           //
        /* l1 = */ 0.5, /* l2 = */ 0.25,                          //
        /* theta1 = */ M_PI * 2 / 3, /* theta2 = */ M_PI * 2 / 3, //
        /* omega1 = */ 0, /* omega2 = */ 0                        //
    );
    p2 = new DoublePendulum(                                              //
        /* m1 = */ 1.0, /* m2 = */ 0.5,                                   //
        /* l1 = */ 0.5, /* l2 = */ 0.25,                                  //
        /* theta1 = */ M_PI * 2 / 3 + 0.001, /* theta2 = */ M_PI * 2 / 3, //
        /* omega1 = */ 0, /* omega2 = */ 0                                //
    );
    p2->setPendulumColor(1, 0, 0);
    p3 = new DoublePendulum(                                               //
        /* m1 = */ 1.0, /* m2 = */ 0.5,                                    //
        /* l1 = */ 0.5, /* l2 = */ 0.25,                                   //
        /* theta1 = */ M_PI * 2 / 3 + 0.0001, /* theta2 = */ M_PI * 2 / 3, //
        /* omega1 = */ 0, /* omega2 = */ 0                                 //
    );
    p3->setPendulumColor(0, 1, 0);
    p4 = new DoublePendulum(                                                //
        /* m1 = */ 1.0, /* m2 = */ 0.5,                                     //
        /* l1 = */ 0.5, /* l2 = */ 0.25,                                    //
        /* theta1 = */ M_PI * 2 / 3 + 0.00001, /* theta2 = */ M_PI * 2 / 3, //
        /* omega1 = */ 0, /* omega2 = */ 0                                  //
    );
    p4->setPendulumColor(0, 0, 1);
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
    p1->step();
    p2->step();
    p3->step();
    p4->step();

    p4->display();
    p3->display();
    p2->display();
    p1->display();
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
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            glutIdleFunc(idle);
        } else if (state == GLUT_UP) {
            glutIdleFunc(0);
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
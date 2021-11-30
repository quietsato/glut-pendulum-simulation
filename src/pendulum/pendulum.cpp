#include "pendulum.hpp"

#include <cmath>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

double omega_dot1(double g, double m1, double m2, double l1, double l2,
                  double theta1, double theta2, double omega1, double omega2) {
    double C = cos(theta1 - theta2);
    double S = sin(theta1 - theta2), s1 = sin(theta1), s2 = sin(theta2);
    double M = m1 + m2;
    return ((g * (s2 * C - (M / m2) * s1)                                //
             - (S * (l1 * omega1 * omega1 * C + l2 * omega2 * omega2)))) //
           /                                                             //
           (l1 * ((M / m2) - C * C));                                    //
}

double omega_dot2(double g, double m1, double m2, double l1, double l2,
                  double theta1, double theta2, double omega1, double omega2) {
    double C = cos(theta1 - theta2);
    double S = sin(theta1 - theta2), s1 = sin(theta1), s2 = sin(theta2);
    double M = m1 + m2;
    return ((g * (M / m2) * (s1 * C - s2)                                     //
             + S * ((M / m2) * l1 * omega1 * omega1 + l2 * omega2 * omega2))) //
           /                                                                  //
           (l2 * ((M / m2) - C * C));                                         //
}

double theta_dot1(double omega1) { return omega1; }
double theta_dot2(double omega2) { return omega2; }

void DoublePendulum::updateCoordinates() {
    this->x1 = l1 * sin(theta1), y1 = -l1 * cos(theta1);
    this->x2 = x1 + l2 * sin(theta2), y2 = y1 - l2 * cos(theta2);
}

void DoublePendulum::clearLocus() {
    this->locus.clear();
    this->locusIndex = 0;
}

void DoublePendulum::recordLocus() {
    if (this->locus.size() < HISTORY_MAX) {
        this->locus.push_back(std::pair<double, double>(x2, y2));
    } else {
        this->locus[this->locusIndex] = std::pair<double, double>(x2, y2);
        this->locusIndex = (this->locusIndex + 1) % HISTORY_MAX;
    }
}

void DoublePendulum::displayLocus() {
    if (this->locus.size() < HISTORY_MAX) {
        glBegin(GL_LINES);
        glColor3d(this->lr, this->lg, this->lb);
        for (size_t i = 0; i < this->locus.size() - 1; i++) {
            glVertex2d(this->locus[i].first, this->locus[i].second);
            glVertex2d(this->locus[i + 1].first, this->locus[i + 1].second);
        }
        glEnd();
    } else {
        glBegin(GL_LINES);
        glColor3d(this->lr, this->lg, this->lb);
        for (size_t j = 0; j < HISTORY_MAX - 1; j++) {
            size_t i1 = (this->locusIndex + j) % HISTORY_MAX;
            size_t i2 = (i1 + 1) % HISTORY_MAX;
            glVertex2d(this->locus[i1].first, this->locus[i1].second);
            glVertex2d(this->locus[i2].first, this->locus[i2].second);
        }
        glEnd();
    }
}

void DoublePendulum::displayPendulum() {
    glBegin(GL_LINES);
    glColor3d(this->pr, this->pg, this->pb);

    glVertex2d(0.0, 0.0);
    glVertex2d(x1, y1);
    glVertex2d(x1, y1);
    glVertex2d(x2, y2);

    glEnd();
}

DoublePendulum::DoublePendulum(                                //
    double m1, double m2, double l1, double l2,                //
    double theta1, double theta2, double omega1, double omega2 //
) {
    this->m1 = m1;
    this->m2 = m2;
    this->l1 = l1;
    this->l2 = l2;
    this->theta1 = theta1;
    this->theta2 = theta2;
    this->omega1 = omega1;
    this->omega2 = omega2;
}

void DoublePendulum::step() {
    double k1_theta1 = h * theta_dot1(omega1);
    double k1_theta2 = h * theta_dot2(omega2);
    double k1_omega1 =                                            //
        h * omega_dot1(                                           //
                g, m1, m2, l1, l2, theta1, theta2, omega1, omega2 //
            );
    double k1_omega2 =                                            //
        h * omega_dot2(                                           //
                g, m1, m2, l1, l2, theta1, theta2, omega1, omega2 //
            );

    double k2_theta1 = h * theta_dot1(omega1 + k1_omega1 / 2);
    double k2_theta2 = h * theta_dot2(omega2 + k1_omega2 / 2);
    double k2_omega1 =
        h * omega_dot1(                                         //
                g, m1, m2, l1, l2,                              //
                theta1 + k1_theta1 / 2, theta2 + k1_theta2 / 2, //
                omega1 + k1_omega1 / 2, omega2 + k1_omega2 / 2  //
            );
    double k2_omega2 =                                          //
        h * omega_dot2(                                         //
                g, m1, m2, l1, l2,                              //
                theta1 + k1_theta1 / 2, theta2 + k1_theta2 / 2, //
                omega1 + k1_omega1 / 2, omega2 + k1_omega2 / 2  //
            );

    double k3_theta1 = h * theta_dot1(omega1 + k2_omega1 / 2);
    double k3_theta2 = h * theta_dot2(omega2 + k2_omega2 / 2);
    double k3_omega1 =                                          //
        h * omega_dot1(                                         //
                g, m1, m2, l1, l2,                              //
                theta1 + k2_theta1 / 2, theta2 + k2_theta2 / 2, //
                omega1 + k2_omega1 / 2, omega2 + k2_omega2 / 2  //
            );
    double k3_omega2 =                                          //
        h * omega_dot2(                                         //
                g, m1, m2, l1, l2,                              //
                theta1 + k2_theta1 / 2, theta2 + k2_theta2 / 2, //
                omega1 + k2_omega1 / 2, omega2 + k2_omega2 / 2  //
            );

    double k4_theta1 = h * theta_dot1(omega1 + k3_omega1);
    double k4_theta2 = h * theta_dot2(omega2 + k3_omega2);
    double k4_omega1 =                                  //
        h * omega_dot1(                                 //
                g, m1, m2, l1, l2,                      //
                theta1 + k3_theta1, theta2 + k3_theta2, //
                omega1 + k3_omega1, omega2 + k3_omega2  //
            );
    double k4_omega2 =                                  //
        h * omega_dot2(                                 //
                g, m1, m2, l1, l2,                      //
                theta1 + k3_theta1, theta2 + k3_theta2, //
                omega1 + k3_omega1, omega2 + k3_omega2  //
            );

    theta1 += (k1_theta1 + 2.0 * k2_theta1 + 2.0 * k3_theta1 + k4_theta1) / 6.0;
    omega1 += (k1_omega1 + 2.0 * k2_omega1 + 2.0 * k3_omega1 + k4_omega1) / 6.0;
    theta2 += (k1_theta2 + 2.0 * k2_theta2 + 2.0 * k3_theta2 + k4_theta2) / 6.0;
    omega2 += (k1_omega2 + 2.0 * k2_omega2 + 2.0 * k3_omega2 + k4_omega2) / 6.0;

    this->updateCoordinates();
    this->recordLocus();
}

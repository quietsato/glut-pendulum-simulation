#pragma once

#include <cmath>

double omega_dot1(double g, double m1, double m2, double l1, double l2,
                  double theta1, double theta2, double omega1, double omega2) {
    return ((g * (sin(theta2) * cos(theta1 - theta2) -
                  (((m1 + m2) / m2) * sin(theta1))) -
             (sin(theta1 - theta2) *
              (l1 * omega1 * omega1 * cos(theta1 - theta2) +
               l2 * omega2 * omega2)))) /
           (l1 *
            (((m1 + m2) / m2) - cos(theta1 - theta2) * cos(theta1 - theta2)));
}

double omega_dot2(double g, double m1, double m2, double l1, double l2,
                  double theta1, double theta2, double omega1, double omega2) {
    return ((g * ((m1 + m2) / m2) *
                 (sin(theta1) * cos(theta1 - theta2) - sin(theta2)) +
             (sin(theta1 - theta2) * (((m1 + m2) / m2) * l1 * omega1 * omega1 +
                                      l2 * omega2 * omega2)))) /
           (l2 *
            (((m1 + m2) / (m2)) - cos(theta1 - theta2) * cos(theta1 - theta2)));
}

double theta_dot1(double omega1) { return omega1; }
double theta_dot2(double omega2) { return omega2; }

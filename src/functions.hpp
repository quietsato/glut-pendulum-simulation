#include <cmath>

double omega_dot1(double g, double m1, double m2, double l1, double l2,
                  double theta1, double theta2, double omega2,
                  double omega_dot2) {
    return (-(m2 * l2 * omega_dot2 * cos(theta1 - theta2)) -
            (m2 * l2 * omega2 * omega2 * sin(theta1 - theta2)) -
            g * (m1 + m2) * sin(theta1)) /
           ((m1 + m2) * l1);
}

double omega_dot2(double g, double m1, double m2, double l1, double l2,
                  double theta1, double theta2, double omega2,
                  double omega_dot1) {
    return ((m2 * l1 * omega_dot1 * sin(theta1 - theta2)) -
            (m2 * l1 * omega_dot1 * cos(theta1 - theta2) -
             (m2 * g * sin(theta2)))) /
           (m2 * l2);
}

double theta_dot1(double omega1) { return omega1; }
double theta_dot2(double omega2) { return omega2; }

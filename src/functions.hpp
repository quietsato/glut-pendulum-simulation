#pragma once

#include <cmath>

double omega_dot1(double g, double m1, double m2, double l1, double l2,
                  double theta1, double theta2, double omega1, double omega2) {
    double C = cos(theta1 - theta2);
    double S = sin(theta1 - theta2);
    double M = m1 + m2;
    return (-(m2 * l1 * l2 * S * m2 * l2 * l2 * omega2 * omega2)      //
            - (m2 * m2 * l1 * l1 * l2 * l2 * C * S * omega1 * omega1) //
            - (M * g * l1 * sin(theta1) * m2 * l2 * l2)               //
            + (m2 * m2 * g * l2 * l2 * C * sin(theta2)))              //
           /                                                          //
           ((M * l1 * l1 * m2 * l2 * l2)                              //
            - (m2 * m2 * l1 * l1 * l2 * l2 * C * C));
}

double omega_dot2(double g, double m1, double m2, double l1, double l2,
                  double theta1, double theta2, double omega1, double omega2) {
    double C = cos(theta1 - theta2);
    double S = sin(theta1 - theta2);
    double M = m1 + m2;
    return (-(m2 * m2 * l1 * l1 * l2 * l2 * C * S * omega2 * omega2) //
            - (M * l1 * l1 * m2 * l1 * l2 * S * omega1 * omega1)     //
            - (M * m2 * g * l1 * l1 * l2 * C * sin(theta1))          //
            + (M * l1 * l1 * m2 * g * l2 * sin(theta2)))             //
           /                                                         //
           ((m2 * m2 * l1 * l1 * l2 * l2 * C * C)                    //
            - (M * l1 * l1 * m2 * l2 * l2));
}

double theta_dot1(double omega1) { return omega1; }
double theta_dot2(double omega2) { return omega2; }

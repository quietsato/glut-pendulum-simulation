#pragma once

#include <vector>

#define HISTORY_MAX 1000

class DoublePendulum {
  private:
    double g = 9.8, h = 0.005;
    double pr = 1, pg = 1, pb = 1;
    double m1, m2, l1, l2, theta1, theta2, omega1, omega2;

    std::vector<std::pair<double, double>> locus;
    size_t locusIndex = 0;

    bool isEnabledLocus = false;

    void recordLocus(double x2, double y2);

  public:
    DoublePendulum(                                                //
        double m1, double m2, double l1, double l2,                //
        double theta1, double theta2, double omega1, double omega2 //
    );
    void step();
    void display();

    void setIsEnabledLocus(bool b) { this->isEnabledLocus = b; }
    void setPendulumColor(double r, double g, double b) {
        this->pr = r;
        this->pg = g;
        this->pb = b;
    }
    void setGravity(double g) { this->g = g; }
    void setStepHeight(double h) { this->h = h; }
};
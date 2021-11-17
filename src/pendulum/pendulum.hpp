#pragma once

#include <vector>

#define HISTORY_MAX 1000

class DoublePendulum {
  private:
    double g = 9.8, h = 0.005;
    double pr = 1, pg = 1, pb = 1;
    double lr = 1, lg = 0, lb = 0;
    double m1, m2, l1, l2, theta1, theta2, omega1, omega2, x1, x2, y1, y2;

    std::vector<std::pair<double, double>> locus;
    size_t locusIndex = 0;

    void updateCoordinates();
    void recordLocus();

  public:
    DoublePendulum(                                                //
        double m1, double m2, double l1, double l2,                //
        double theta1, double theta2, double omega1, double omega2 //
    );
    void step();

    void displayLocus();
    void displayPendulum();

    void setPendulumColor(double r, double g, double b) {
        this->pr = r;
        this->pg = g;
        this->pb = b;
    }
    void setLocusColor(double r, double g, double b) {
        this->lr = r;
        this->lg = g;
        this->lb = b;
    }
    void setGravity(double g) { this->g = g; }
    void setStepHeight(double h) { this->h = h; }
};
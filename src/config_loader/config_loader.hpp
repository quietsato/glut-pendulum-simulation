#pragma once

#include "../../lib/yaml-cpp/include/yaml-cpp/yaml.h"

#include <string>
#include <vector>

typedef struct PendulumConfig {
    double m1;
    double m2;
    double l1;
    double l2;
    double theta1_deg;
    double theta2_deg;
    double omega1_deg;
    double omega2_deg;
} PendulumConfig;

namespace config_loader {
std::vector<PendulumConfig> load(std::string path);
}
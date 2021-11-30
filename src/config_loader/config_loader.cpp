
#include "config_loader.hpp"
#include <iostream>

void load() {
    YAML::Node config = YAML::LoadFile("../example/01-simple.yaml");
    std::cout << config << std::endl;
}

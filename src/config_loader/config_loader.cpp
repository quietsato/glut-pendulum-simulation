
#include "config_loader.hpp"
#include <iostream>
#include <vector>

#define set_config(dest, src, def, key)                                        \
    if (src[#key].IsDefined()) {                                               \
        dest.key = src[#key].as<typeof dest.key>();                            \
    } else if (def[#key].IsDefined()) {                                        \
        dest.key = def[#key].as<typeof dest.key>();                            \
    } else {                                                                   \
        exit(1);                                                               \
    }

std::vector<PendulumConfig> config_loader::load(std::string path) {
    YAML::Node config = YAML::LoadFile(path);

    YAML::Node default_pendulum = config["default_pendulum"];
    assert(default_pendulum.IsDefined());
    assert(default_pendulum.IsMap());

    YAML::Node pendulums = config["pendulums"];
    assert(pendulums.IsDefined());
    assert(pendulums.IsSequence());

    std::vector<PendulumConfig> p;
    for (YAML::Node pendulum : pendulums) {
        PendulumConfig c;
        set_config(c, pendulum, default_pendulum, l1);
        set_config(c, pendulum, default_pendulum, l2);
        set_config(c, pendulum, default_pendulum, m1);
        set_config(c, pendulum, default_pendulum, m2);
        set_config(c, pendulum, default_pendulum, theta1_deg);
        set_config(c, pendulum, default_pendulum, theta2_deg);
        set_config(c, pendulum, default_pendulum, omega1_deg);
        set_config(c, pendulum, default_pendulum, omega2_deg);
        p.push_back(c);
    }

    return p;
}

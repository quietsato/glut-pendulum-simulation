cmake_minimum_required(VERSION 3.10.3)
project(glut_pendulum_simulation CXX)

set (CMAKE_CXX_STANDARD 11)

add_executable(
    pendulum.out 
    ./src/main.cpp
    ./src/pendulum/pendulum.hpp
    ./src/pendulum/pendulum.cpp
)

if (APPLE)
    # macOS
    set(CMAKE_CXX_FLAGS "-framework GLUT -framework OpenGL")
else ()
    # Linux
    target_link_libraries(pendulum.out glut GL GLU m)
endif ()

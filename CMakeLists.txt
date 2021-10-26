cmake_minimum_required(VERSION 3.1)
project(glut_pendulum_simulation CXX)

set (CMAKE_CXX_STANDARD 11)

if (APPLE)
    # macOS
    set(CMAKE_CXX_FLAGS "-framework GLUT -framework OpenGL")
else ()
    # TODO:
    # Linux or so on
    # set(CMAKE_CXX_FLAGS "") 
endif ()


add_executable(pendulum.out ./src/main.cpp)

cmake_minimum_required(VERSION 3.10)
project(glutSceneManager)

set(CMAKE_CXX_STANDARD 11)

include(FindPkgConfig)

pkg_check_modules (COIN3D Coin REQUIRED)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(${COIN3D_INCLUDE_DIRS} ${GLUT_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR})

add_subdirectory(example1)
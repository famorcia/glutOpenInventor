cmake_minimum_required(VERSION 3.24)
project(glutSceneManager)

set(CMAKE_CXX_STANDARD 11)

include(FindPkgConfig)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
pkg_check_modules (COIN3D Coin REQUIRED)

include_directories(${COIN3D_INCLUDE_DIRS} ${GLUT_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR})

add_subdirectory(example1)
add_subdirectory(from_glut-3.7)
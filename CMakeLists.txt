cmake_minimum_required(VERSION 3.24)
project(glutSceneManager)

set(CMAKE_CXX_STANDARD 11)

include(FindPkgConfig)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include(FetchContent)

FetchContent_Declare(Coin
        GIT_REPOSITORY  https://github.com/coin3d/coin.git
        GIT_TAG         v4.0.6
        GIT_SHALLOW     TRUE
        FIND_PACKAGE_ARGS
)

message(STATUS "Download and build Coin3D if necessary, please wait...")
FetchContent_MakeAvailable(Coin)
message(STATUS "Download and build Coin3D - done.")

#pkg_check_modules (COIN3D Coin)
#message(FATAL_ERROR ${COIN3D_INCLUDE_DIRS})
include_directories(${COIN3D_INCLUDE_DIRS} ${GLUT_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR})

add_subdirectory(example1)
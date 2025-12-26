cmake_minimum_required(VERSION 3.10)
project(glutSceneManager)

set(CMAKE_CXX_STANDARD 11)

include(FindPkgConfig)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

pkg_check_modules (COIN3D Coin)

if(NOT COIN3D)
    include(FetchContent)

    FetchContent_Declare(Coin3D
            GIT_REPOSITORY  https://github.com/coin3d/coin.git
            GIT_TAG         v4.0.6
            GIT_SHALLOW     TRUE
    )

    message(STATUS "Download and build Coin3D if necessary, please wait...")
    FetchContent_MakeAvailable(Coin3D)
    message(STATUS "Download and build Coin3D - done.")
endif ()

include_directories(${COIN3D_INCLUDE_DIRS} ${GLUT_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR})

add_subdirectory(example1)
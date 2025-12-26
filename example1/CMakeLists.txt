
add_executable(glutSceneManager main.cpp)

target_link_libraries(glutSceneManager ${COIN3D_LINK_LIBRARIES} ${GLUT_LIBRARIES} ${OPENGL_LIBRARIES})

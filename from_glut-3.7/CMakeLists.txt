
add_executable(globe globe.c++)

target_link_libraries(globe ${COIN3D_LINK_LIBRARIES} ${GLUT_LIBRARIES} ${OPENGL_LIBRARIES})

add_executable(glutduck glutduck.c++)

target_link_libraries(glutduck ${COIN3D_LINK_LIBRARIES} ${GLUT_LIBRARIES} ${OPENGL_LIBRARIES})

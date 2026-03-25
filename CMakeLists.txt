cmake_minimum_required(VERSION 2.8...3.5)

project(COSC363_Assignment-1)

add_executable(scene.out src/scene.cpp src/alien.cpp src/peopleSpinner.cpp)

set(OpenGL_GL_PREFERENCE LEGACY)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

target_include_directories(scene.out PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_link_libraries( scene.out ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} )

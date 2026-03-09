cmake_minimum_required(VERSION 2.8...3.5)

project(Assignment1)

add_executable(Scene.out src/Scene.cpp)

set(OpenGL_GL_PREFERENCE LEGACY)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

target_link_libraries( Scene.out ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} )

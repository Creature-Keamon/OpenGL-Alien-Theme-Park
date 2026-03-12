cmake_minimum_required(VERSION 2.8...3.5)

project(COSC363_Assignment-1)

add_executable(Scene.out src/Scene.cpp src/Alien.cpp)

set(OpenGL_GL_PREFERENCE LEGACY)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

target_include_directories(Scene.out PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_link_libraries( Scene.out ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} )

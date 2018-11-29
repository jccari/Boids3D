cmake_minimum_required(VERSION 3.12)
project(Boids3D)

set(CMAKE_CXX_STANDARD 14)

set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})


add_executable(Boids3D main.cpp tools/Vector3D.h Boid.h tools/Vector3DHasher.h tools/Grid.h Flock.h)

target_link_libraries(Boids3D ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
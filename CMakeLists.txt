cmake_minimum_required(VERSION 3.8)
project(Boids_)

# Set Global Variables
set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Boid.cpp Boid.h Flock.cpp Flock.h Scene.cpp Scene.h Common.h Vector.cpp Vector.h SceneController.cpp SceneController.h)
add_executable(Boids_ ${SOURCE_FILES})

# OpenGL Import
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${OPENGL_INCLUDE_DIRS})

# GLFW Import
add_subdirectory(glfw)
include_directories(glfw/include)
target_link_libraries(${PROJECT_NAME} glfw ${GLFW_LIBRARIES})
target_link_libraries(${PROJECT_NAME} glfw ${OPENGL_glu_LIBRARY} ${GLFW_LIBRARIES})

# TBB Import
add_subdirectory(tbb)
include_directories(tbb/include)
target_link_libraries(${PROJECT_NAME} tbb)


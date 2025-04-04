cmake_minimum_required(VERSION 3.2)
project(flocksim)

cmake_policy(SET CMP0072 NEW)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})
link_directories(${GLFW_LIBRARY_DIRS})

include_directories(/usr/include/glm)

add_executable(${PROJECT_NAME} boid.cpp main.cpp)
target_link_libraries(${PROJECT_NAME} ${GLFW_LIBRARIES} OpenGL::GL GLEW::GLEW)

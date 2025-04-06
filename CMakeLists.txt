cmake_minimum_required(VERSION 3.2)
project(flocksim)

set(CMAKE_CXX_STANDARD 17)

cmake_policy(SET CMP0072 NEW)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm CONFIG REQUIRED)

add_executable(${PROJECT_NAME} boid.cpp main.cpp)

target_link_libraries(${PROJECT_NAME} glfw OpenGL::GL GLEW::GLEW glm::glm)

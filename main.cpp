#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include <cstdlib>
#include "boid.h"

const int WIDTH = 800, HEIGHT = 800, NUM_AGENTS = 500;

using namespace std;

void initOpenGL() {
    glewExperimental = GL_TRUE;
    glewInit();
    glViewport(0, 0, WIDTH, HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, WIDTH, HEIGHT, 0, -1, 1);
}



int main() {
    if (!glfwInit()) return -1;
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Flocking Simulation", NULL, NULL);
    glfwMakeContextCurrent(window);
    initOpenGL();

    vector<Boid> boids;
    for (int i = 0; i < NUM_AGENTS; ++i)
        boids.emplace_back(rand() % WIDTH, rand() % HEIGHT);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        
        vector<Boid> previous = boids;
        for (int i = 0; i < NUM_AGENTS; i++){
            boids[i].update(previous);
            boids[i].draw();
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}


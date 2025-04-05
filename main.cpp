#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <cstdlib>
#include "boid.h"
#include "constants.h"

using namespace std;

void initOpenGL() {
    glewExperimental = GL_TRUE;
    glewInit();
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, constants::WIDTH, constants::HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float maxViewDist = glm::length(glm::vec3(constants::WIDTH, constants::HEIGHT, constants::DEPTH) + 800.f);
    glm::mat4 projection = glm::perspective(glm::radians(60.0f), float(constants::WIDTH) / constants::HEIGHT, 1.0f, maxViewDist);
    glLoadMatrixf(glm::value_ptr(projection));

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glm::mat4 view = glm::lookAt(
        glm::vec3(constants::WIDTH - 200, constants::HEIGHT - 200, 1050),
        glm::vec3(constants::WIDTH / 2, constants::HEIGHT / 2, 0),
        glm::vec3(0, 1, 0)
    );
    glLoadMatrixf(glm::value_ptr(view));
}

void drawBoundingBox(float width, float height, float depth) {
    glm::vec3 corners[8] = {
        glm::vec3(0, height, depth), // Top front-left
        glm::vec3(width, height, depth),  // Top front-right
        glm::vec3(0, height, 0), // Top back-left
        glm::vec3(width, height, 0),  // Top back-right
        glm::vec3(0, 0, depth), // Bottom front-left
        glm::vec3(width, 0, depth),  // Bottom front-right
        glm::vec3(0, 0, 0), // Bottom back-left
        glm::vec3(width, 0, 0)   // Bottom back-right
    };

    glBegin(GL_LINES);
    // Top face (front and back)
    glVertex3f(corners[0].x, corners[0].y, corners[0].z); glVertex3f(corners[1].x, corners[1].y, corners[1].z);
    glVertex3f(corners[1].x, corners[1].y, corners[1].z); glVertex3f(corners[3].x, corners[3].y, corners[3].z);
    glVertex3f(corners[3].x, corners[3].y, corners[3].z); glVertex3f(corners[2].x, corners[2].y, corners[2].z);
    glVertex3f(corners[2].x, corners[2].y, corners[2].z); glVertex3f(corners[0].x, corners[0].y, corners[0].z);

    // Bottom face (front and back)
    glVertex3f(corners[4].x, corners[4].y, corners[4].z); glVertex3f(corners[5].x, corners[5].y, corners[5].z);
    glVertex3f(corners[5].x, corners[5].y, corners[5].z); glVertex3f(corners[7].x, corners[7].y, corners[7].z);
    glVertex3f(corners[7].x, corners[7].y, corners[7].z); glVertex3f(corners[6].x, corners[6].y, corners[6].z);
    glVertex3f(corners[6].x, corners[6].y, corners[6].z); glVertex3f(corners[4].x, corners[4].y, corners[4].z);

    // Vertical edges (connecting top and bottom faces)
    glVertex3f(corners[0].x, corners[0].y, corners[0].z); glVertex3f(corners[4].x, corners[4].y, corners[4].z);
    glVertex3f(corners[1].x, corners[1].y, corners[1].z); glVertex3f(corners[5].x, corners[5].y, corners[5].z);
    glVertex3f(corners[3].x, corners[3].y, corners[3].z); glVertex3f(corners[7].x, corners[7].y, corners[7].z);
    glVertex3f(corners[2].x, corners[2].y, corners[2].z); glVertex3f(corners[6].x, corners[6].y, corners[6].z);
    glEnd();
}


int main() {
    if (!glfwInit()) return -1;
    GLFWwindow* window = glfwCreateWindow(constants::WIDTH, constants::HEIGHT, "Flocking Simulation", NULL, NULL);
    glfwMakeContextCurrent(window);
    initOpenGL();

    vector<Boid> boids;
    for (int i = 0; i < constants::NUM_AGENTS; ++i) {
        float x = static_cast<float>(rand()) / RAND_MAX * constants::WIDTH;
        float y = static_cast<float>(rand()) / RAND_MAX * constants::HEIGHT;
        float z = static_cast<float>(rand()) / RAND_MAX * constants::DEPTH;
        boids.emplace_back(x, y, z);
    }

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glColor3f(255,255,255);
        drawBoundingBox(constants::WIDTH, constants::HEIGHT, constants::DEPTH);

        vector<Boid> previous = boids;
        for (int i = 0; i < constants::NUM_AGENTS; i++){
            boids[i].update(previous);
            boids[i].draw();
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}


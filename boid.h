#ifndef BOID_H
#define BOID_H

#include <glm/glm.hpp>
#include <vector>

class Boid {
public:
    Boid(float x, float y, float z);

    void update(std::vector<Boid>& boids);
    void draw();

    glm::vec3 position, velocity;

private:
    const float MAX_SPEED = 5.f;
    const float MIN_SPEED = 0.5f;
    const float NEIGHBOR_RADIUS = 50.0f;

    // helper function to draw cone pointing toward direction of velocity
    void drawCone(float radius, float h, int slices);
};

#endif

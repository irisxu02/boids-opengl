#ifndef BOID_H
#define BOID_H

#include <glm/glm.hpp>
#include <vector>

class Boid {
public:
    Boid(float x, float y);

    void update(std::vector<Boid>& boids);
    void draw();

    glm::vec2 position, velocity;

private:
    const float MAX_SPEED = 5.f;
    const float MIN_SPEED = 0.5f;
    const float NEIGHBOR_RADIUS = 50.0f;
};

#endif

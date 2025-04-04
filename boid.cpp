#include <GLFW/glfw3.h>
#include <glm/gtx/norm.hpp>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <random>
#include "boid.h"


using namespace glm;

Boid::Boid(float x, float y) {
    position = vec2(x, y);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<float> dis(0.0f, 1.0f); 
    vec2 dir = vec2(dis(gen), dis(gen));
    velocity = normalize(dir) * MAX_SPEED;
}

void Boid::update(std::vector<Boid>& boids) {
    std::vector<Boid*> neighbors;

    for (auto& other : boids) {
        if (&other == this) continue;
        if (length(position - other.position) < NEIGHBOR_RADIUS) {
            neighbors.push_back(&other);
        }
    }

    std::sort(neighbors.begin(), neighbors.end(), [this](Boid* a, Boid* b) {
        return length2(position - a->position) < length2(position - b->position);
    });

    if (neighbors.size() > 7) neighbors.resize(7);


    vec2 alignment(0, 0); // average of neighbours' velocity
    vec2 attraction(0, 0); // center of mass - position
    vec2 avoidance(0, 0); // sum of direction away from neighbours / distance
    int count = neighbors.size();

    if (count > 0) {
        vec2 center(0, 0);
        for (auto* n : neighbors) {
            alignment += n->velocity;
            center += n->position;

            vec2 diff = position - n->position;
            float dist = length(diff);
            if (dist > 0) avoidance += diff / dist;
        }
        alignment *= (1.f / count);
        attraction = ((center * (1.f / count)) - position); 
    }
    
    float alignmentWeight = 0.5f;
    float attractionWeight = 0.5f;
    float avoidanceWeight = 1.5f;

    vec2 acceleration = alignment * alignmentWeight +
                        attraction * attractionWeight +
                        avoidance * avoidanceWeight;

    velocity += acceleration;
    float speed = length(velocity);
    if (speed > MAX_SPEED)
        velocity = normalize(velocity) * MAX_SPEED;
    else if (speed < MIN_SPEED)
        velocity = normalize(velocity) * MIN_SPEED;

    position += velocity;

    // Turn around border
    const int WIDTH = 800, HEIGHT = 800;
    const float turn_factor = 0.5f;
    const int border = 100;
    if (position.x < border) velocity.x += turn_factor;
    if (position.x > WIDTH-border) velocity.x -= turn_factor;
    if (position.y < border) velocity.y += turn_factor;
    if (position.y > HEIGHT-border) velocity.y -= turn_factor;
}

void Boid::draw() {
    glBegin(GL_TRIANGLES);
    glColor3f(velocity.x, velocity.y, 1.f);
    glVertex2f(position.x, position.y);
    glVertex2f(position.x - 5, position.y + 10);
    glVertex2f(position.x + 5, position.y + 10);
    glEnd();
}


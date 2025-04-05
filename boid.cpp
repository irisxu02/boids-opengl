#include <GLFW/glfw3.h>
#include <glm/gtx/norm.hpp>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <random>
#include "boid.h"
#include "constants.h"

using namespace glm;

Boid::Boid(float x, float y, float z) {
    position = vec3(x, y, z);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<float> dis(0.0f, 1.0f); 
    vec3 dir = vec3(dis(gen), dis(gen), dis(gen));
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


    vec3 alignment(0, 0, 0); // average of neighbours' velocity
    vec3 attraction(0, 0, 0); // center of mass - position
    vec3 avoidance(0, 0, 0); // sum of direction away from neighbours / distance
    int count = neighbors.size();

    if (count > 0) {
        vec3 center(0, 0, 0);
        for (auto* n : neighbors) {
            alignment += n->velocity;
            center += n->position;

            vec3 diff = position - n->position;
            float dist = length(diff);
            if (dist > 0) avoidance += diff / dist;
        }
        alignment *= (1.f / count);
        attraction = ((center * (1.f / count)) - position); 
    }
    
    float alignmentWeight = 0.5f;
    float attractionWeight = 0.5f;
    float avoidanceWeight = 1.5f;

    vec3 acceleration = alignment * alignmentWeight + attraction * attractionWeight + avoidance * avoidanceWeight;

    velocity += acceleration;
    float speed = length(velocity);
    if (speed > MAX_SPEED)
        velocity = normalize(velocity) * MAX_SPEED;
    else if (speed < MIN_SPEED)
        velocity = normalize(velocity) * MIN_SPEED;

    position += velocity;

    // Turn around border
    const float turn_factor = 0.5f;
    const int border = 100;
    if (position.x < border) velocity.x += turn_factor;
    if (position.x > constants::WIDTH-border) velocity.x -= turn_factor;
    if (position.y < border) velocity.y += turn_factor;
    if (position.y > constants::HEIGHT-border) velocity.y -= turn_factor;
    if (position.z < border) velocity.z += turn_factor;
    if (position.z > constants::DEPTH-border) velocity.z -= turn_factor;
}

void Boid::draw() {
    glPushMatrix();
    glTranslatef(position.x, position.y, position.z);
    drawCone(2.f, 5.f, 20);
    glPopMatrix();
}

void Boid::drawCone(float radius, float h, int slices) {
    glBegin(GL_TRIANGLE_FAN);
    vec3 normV = normalize(velocity);
    vec3 rgb = vec3(abs(normV.x), abs(normV.y), abs(normV.z));
    glColor3f(rgb.x, rgb.y, rgb.z); // TODO: maybe change to color by magnitude (speed)
    glVertex3f(velocity.x, velocity.y, velocity.z);
    for (int i = 0; i <= slices; ++i) {
        float angle = 2.0f * M_PI * i / slices;
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex3f(x, y, -h);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0f, 0.0f, -h);
    for (int i = 0; i <= slices; ++i) {
        float angle = 2.0f * M_PI * i / slices;
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex3f(x, y, -h);
    }
    glEnd();
}
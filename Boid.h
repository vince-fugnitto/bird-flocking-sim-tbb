#ifndef BOIDS_BOID_H
#define BOIDS_BOID_H

#include <vector>
#include <random>
#include <cmath>
#include <tbb/task_group.h>
#include "Common.h"
#include "Vector.h"

class Boid
{
  public:
    Vector location;
    Vector velocity;
    Vector acceleration;
    float r;
    float maxForce;
    float maxSpeed;

    float randomWidthStart();
    float randomHeightStart();
    float randomFloat();

    Boid();

    Boid(Vector loc, float speed, float force);

    void run(std::vector<Boid> boids);

    void flock(std::vector<Boid> boids);

    void update();

    Vector steer(Vector target, bool slowdown);

    void borders();

    // Flocking Behavior Rules
    Vector separate(std::vector<Boid> boids);

    Vector align(std::vector<Boid> boids);

    Vector cohesion(std::vector<Boid> boids);
};

#endif //BOIDS_BOID_H

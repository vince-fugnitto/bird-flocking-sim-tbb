#ifndef BOIDS_FLOCK_H
#define BOIDS_FLOCK_H

#include <thread>
#include "Boid.h"
#include "Common.h"

class Flock {
public:
    // Class Members
    Color color;
    std::vector<Boid> boids;

    // Class Functions
    Flock();

    void run( Color color);
};

#endif //BOIDS_FLOCK_H

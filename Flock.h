#ifndef BOIDS_FLOCK_H
#define BOIDS_FLOCK_H

#include <thread>
#include <vector>
#include "Boid.h"
#include "Common.h"
#include "tbb/task_group.h"
#include <tbb/parallel_for.h>

class Flock {
public:
    Color color;
    std::vector<Boid> boids;

    Flock();

    void runFlock(Color color);
};

#endif //BOIDS_FLOCK_H

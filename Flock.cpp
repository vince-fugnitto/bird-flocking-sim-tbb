#include "Flock.h"

Flock::Flock() {
    boids.clear();
    for (int i = 0; i < flockSize; i++) {
        Boid b;
        b = Boid(Vector(b.randomWidthStart(), b.randomHeightStart()), 1.0f, 0.01f);
        boids.push_back(b);
    }
}

void Flock::runFlock() {
    tbb::task_group boidTask;

    for (auto &boid : boids) {
        boidTask.run([&] {boid.run(boids);});
    }
    boidTask.wait();
}
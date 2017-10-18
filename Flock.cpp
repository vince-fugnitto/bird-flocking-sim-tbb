#include "Flock.h"

Flock::Flock() {
    boids.clear();
    for (int i = 0; i < flockSize; i++) {
        Boid b = Boid(Vector(b.randomWidthStart(), b.randomHeightStart()), 1.0f, 0.01f);
        boids.push_back(b);
    }
}

void Flock::run(Color color) {
    for (auto &b : boids) {
        b.run(color, boids);
    }
}

#ifndef BOIDS_SCENE_H
#define BOIDS_SCENE_H

#include <iostream>
#include <pthread.h>
#include <tbb/task_group.h>
#include "Common.h"
#include "Flock.h"


class Scene {
public:
    std::vector<Flock> initializeFlock();
    void executeScene();
    void renderFlock(Flock flock);
    void render(Boid boid, Color color);
};

#endif //BOIDS_SCENE_H

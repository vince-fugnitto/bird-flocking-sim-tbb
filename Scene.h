#ifndef BOIDS_SCENE_H
#define BOIDS_SCENE_H

#include <iostream>
#include <pthread.h>
#include "Flock.h"
#include "Common.h"
#include "tbb/tbb_thread.h"


class Scene {
public:
    void executeScene();
};

#endif //BOIDS_SCENE_H

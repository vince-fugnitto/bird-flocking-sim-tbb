#ifndef BOIDS_SCENECONTROLLER_H
#define BOIDS_SCENECONTROLLER_H

#include "Flock.h"

class SceneController {
public:
    // initialize flock
    std::vector<Flock> initializeFlock();
};


#endif //BOIDS_SCENECONTROLLER_H

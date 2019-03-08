#ifndef BOIDS_COMMON_H
#define BOIDS_COMMON_H

#include <GLFW/glfw3.h>

typedef struct
{
    GLfloat r, g, b, a;
} Color;

const int width = 1400;
const int height = 1050;
const int flockSize = 80;

// Boid Colors
const Color purple = {0.70, 0.53, 1.00, 1.0f};
const Color pink = {1.00, 0.41, 0.71, 1.0f};
const Color blue = {0.13, 0.59, 0.95, 1.0f};
const Color yellow = {1.00, 1.00, 0.00, 1.0f};
const Color green = {0.41, 0.94, 0.68, 1.0f};
const Color white = {1.0, 1.00, 1.00, 1.0f};
const Color red = {1.00, 0.09, 0.27, 1.0f};

// Window Background Color
const Color windowColor = {0.02, 0.03, 0.11, 1};

#endif //BOIDS_COMMON_H

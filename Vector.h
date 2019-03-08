
#ifndef BOIDS_VECTOR3D_H
#define BOIDS_VECTOR3D_H

#include <cmath>

class Vector
{
  public:
    float x;
    float y;
    float z;

    Vector(float xValue, float yValue, float zValue);

    Vector(float xValue, float yValue);

    Vector();

    void setXYZ(float xValue, float yValue, float zValue);

    float magnitude();

    Vector copy();

    void add(Vector v);

    void multiply(float n);

    void div(float n);

    void normalize();

    void limit(float max);

    float heading();

    Vector subtract(Vector v1, Vector v2);

    float distance(Vector v1, Vector v2);
};

#endif //BOIDS_VECTOR3D_H

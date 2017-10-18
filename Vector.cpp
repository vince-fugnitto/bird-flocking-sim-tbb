#include "Vector.h"

Vector::Vector(float xValue, float yValue, float zValue) {
    x = xValue;
    y = yValue;
    z = zValue;
}

Vector::Vector(float xValue, float yValue) {
    x = xValue;
    y = yValue;
    z = 0.0f;
}

Vector::Vector() {
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
}

void Vector::setXYZ(float xValue, float yValue, float zValue) {
    x = xValue;
    y = yValue;
    z = zValue;
}

float Vector::magnitude() {
    return sqrtf(x * x + y * y + z * z);
}

Vector Vector::copy() {
    return {x, y, z};
}

void Vector::add(Vector v) {
    x += v.x;
    y += v.y;
    z += v.z;
}

void Vector::multiply(float n) {
    x *= n;
    y *= n;
    z *= n;
}

void Vector::div(float n) {
    x /= n;
    y /= n;
    z /= n;
}

void Vector::normalize() {
    float m = magnitude();
    if (m > 0) {
        div(m);
    }
}

void Vector::limit(float max) {
    if (magnitude() > max) {
        normalize();
        multiply(max);
    }
}

float Vector::heading() {
    float angle = atan2f(y, x);
    return angle;
}

Vector Vector::subtract(Vector v1, Vector v2) {
    Vector v = Vector(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
    return v;
}

float Vector::distance(Vector v1, Vector v2) {
    float dx = v1.x - v2.x;
    float dy = v1.y - v2.y;
    float dz = v1.z - v2.z;
    return sqrtf(dx * dx + dy * dy + dz * dz);
}
#include "Boid.h"
#include <iostream>

float const pi = 3.14159;

float Boid::randomWidthStart() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist(0.0f, width);
    return dist(mt);
}

float Boid::randomHeightStart() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist(0.0f, height);
    return dist(mt);
}

float Boid::randomFloat() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist(-1.0f, 1.0f);
    return dist(mt);
}

float toRadians(float degrees) {
    return (float)(degrees * (pi / 180.0));
}

Boid::Boid(Vector loc, float speed, float force) {
    acceleration = Vector(0, 0);
    velocity = Vector(randomFloat(), randomFloat());
    location = loc.copy();
    r = 0.2f;
    maxSpeed = speed;
    maxForce = force;
}



void Boid::run(Color color, std::vector<Boid> boids) {
    flock(boids);
    update();
    borders();
    render(color);
}

void Boid::flock(std::vector<Boid> boids) {
    Vector separateVector = separate(boids);
    Vector alignVector = align(boids);
    Vector cohereVector = cohesion(boids);

    separateVector.multiply(2.0f);
    alignVector.multiply(1.0f);
    cohereVector.multiply(1.0f);

    acceleration.add(separateVector);
    acceleration.add(alignVector);
    acceleration.add(cohereVector);
}

void Boid::update() {
    velocity.add(acceleration);
    velocity.limit(maxSpeed);
    location.add(velocity);
    acceleration.setXYZ(0, 0, 0);
}

Vector Boid::steer(Vector target, bool slowdown) {
    Vector steer;
    Vector desired = target.subtract(target, location);
    float d = desired.magnitude();

    if (d > 0) {
        desired.normalize();
        if ((slowdown) && (d < 100.0f)) desired.multiply(maxSpeed * (d / 100.0f));
        else desired.multiply(maxSpeed);
        steer = target.subtract(desired, velocity);
        steer.limit(maxForce);
    } else {
        steer = Vector(0, 0);
    }
    return steer;
}

void Boid::render(Color color) {

    float radians = (velocity.heading() + toRadians(270));
    float degrees = (radians * (180 / pi));

    glPushMatrix();
    glTranslatef(location.x, location.y, 0);
    glRotatef (degrees, 0.0, 0.0, 1.0);
    glTranslatef(-location.x, -location.y, 0);

    glBegin(GL_TRIANGLES);
    glColor4f(color.r, color.g, color.b, color.a);
    glVertex2f(location.x, location.y + 5.5f);
    glVertex2f(location.x + 2.5f, location.y - 5.5f);
    glVertex2f(location.x - 2.5f, location.y - 5.5f);
    glEnd();

    glPopMatrix();
}


void Boid::borders() {
    if (location.x < -r) location.x = width + r;
    if (location.y < -r) location.y = height + r;
    if (location.x > width + r) location.x = -r;
    if (location.y > height + r) location.y = -r;
}

Vector Boid::separate(std::vector<Boid> boids) {
    float desiredSeparation = 25.0f;
    Vector sum = Vector(0, 0, 0);
    int count = 0;

    for (auto &b : boids) {
        float d = location.distance(location, b.location);
        if ((d > 0) && (d < desiredSeparation)) {
            Vector diff = location.subtract(location, b.location);
            diff.normalize();
            diff.div(d);
            sum.add(diff);
            count++;
        }
    }
    if (count > 0) {
        sum.div((float) count);
    }
    return sum;
}

Vector Boid::align(std::vector<Boid> boids) {
    float nDistance = 50.0f;
    Vector sum = Vector(0, 0, 0);
    int count = 0;
    for (auto &b : boids) {
        float d = location.distance(location, b.location);
        if ((d > 0) && (d < nDistance)) {
            sum.add(b.velocity);
            count++;
        }
    }
    if (count > 0) {
        sum.div((float) count);
        sum.limit(maxForce);
    }
    return sum;
}

Vector Boid::cohesion(std::vector<Boid> boids) {
    float nDistance = 50.0f;
    Vector sum = Vector(0, 0, 0);
    int count = 0;
    for (auto &b : boids) {
        float d = location.distance(location, b.location);
        if ((d > 0) && (d < nDistance)) {
            sum.add(b.location);
            count++;
        }
    }
    if (count > 0) {
        sum.div((float) count);
        return steer(sum, false);
    }
    return sum;
}

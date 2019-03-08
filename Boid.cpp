#include "Boid.h"
#include <iostream>

float const pi = 3.14159;

float Boid::randomWidthStart()
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist(0.0f, width);
    return dist(mt);
}

float Boid::randomHeightStart()
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist(0.0f, height);
    return dist(mt);
}

float Boid::randomFloat()
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist(-1.0f, 1.0f);
    return dist(mt);
}

Boid::Boid() {}

Boid::Boid(Vector loc, float speed, float force)
{
    acceleration = Vector(0, 0);
    velocity = Vector(randomFloat(), randomFloat());
    location = loc.copy();
    r = 0.2f;
    maxSpeed = speed;
    maxForce = force;
}

void Boid::run(std::vector<Boid> boids)
{
    flock(boids);
    update();
    borders();
}

void Boid::flock(std::vector<Boid> boids)
{

    Vector separateVector;
    Vector alignVector;
    Vector cohereVector;

    // apply bird flocking rules in parallel
    tbb::task_group taskGroup;

    // spawn threads
    taskGroup.run([&] { separateVector = separate(boids); });
    taskGroup.run([&] { (alignVector = align(boids)); });
    taskGroup.run([&] { (cohereVector = cohesion(boids)); });

    // synchronize threads
    taskGroup.wait();

    separateVector.multiply(2.0f);
    alignVector.multiply(1.0f);
    cohereVector.multiply(1.0f);

    acceleration.add(separateVector);
    acceleration.add(alignVector);
    acceleration.add(cohereVector);
}

void Boid::update()
{
    velocity.add(acceleration);
    velocity.limit(maxSpeed);
    location.add(velocity);
    acceleration.setXYZ(0, 0, 0);
}

Vector Boid::steer(Vector target, bool slowdown)
{
    Vector steer;
    Vector desired = target.subtract(target, location);
    float d = desired.magnitude();

    if (d > 0)
    {
        desired.normalize();
        if ((slowdown) && (d < 100.0f))
        {
            desired.multiply(maxSpeed * (d / 100.0f));
        }
        else
        {
            desired.multiply(maxSpeed);
        }
        steer = target.subtract(desired, velocity);
        steer.limit(maxForce);
    }
    else
    {
        steer = Vector(0, 0);
    }
    return steer;
}

void Boid::borders()
{
    if (location.x < -r)
    {
        location.x = width + r;
    }
    if (location.y < -r)
    {
        location.y = height + r;
    }
    if (location.x > width + r)
    {
        location.x = -r;
    }
    if (location.y > height + r)
    {
        location.y = -r;
    }
}

Vector Boid::separate(std::vector<Boid> boids)
{
    float desiredSeparation = 25.0f;
    Vector sum = Vector(0, 0, 0);
    int count = 0;

    for (auto &b : boids)
    {
        float d = location.distance(location, b.location);
        if ((d > 0) && (d < desiredSeparation))
        {
            Vector diff = location.subtract(location, b.location);
            diff.normalize();
            diff.div(d);
            sum.add(diff);
            count++;
        }
    }
    if (count > 0)
    {
        sum.div((float)count);
    }
    return sum;
}

Vector Boid::align(std::vector<Boid> boids)
{
    float nDistance = 50.0f;
    Vector sum = Vector(0, 0, 0);
    int count = 0;
    for (auto &b : boids)
    {
        float d = location.distance(location, b.location);
        if ((d > 0) && (d < nDistance))
        {
            sum.add(b.velocity);
            count++;
        }
    }
    if (count > 0)
    {
        sum.div((float)count);
        sum.limit(maxForce);
    }
    return sum;
}

Vector Boid::cohesion(std::vector<Boid> boids)
{
    float nDistance = 50.0f;
    Vector sum = Vector(0, 0, 0);
    int count = 0;
    for (auto &b : boids)
    {
        float d = location.distance(location, b.location);
        if ((d > 0) && (d < nDistance))
        {
            sum.add(b.location);
            count++;
        }
    }
    if (count > 0)
    {
        sum.div((float)count);
        return steer(sum, false);
    }
    return sum;
}

#include "Scene.h"

float const pi = 3.14159;

std::vector<Flock> Scene::initializeFlock()
{

    // flock container
    std::vector<Flock> flockList;

    // create flocks
    Flock a = Flock();
    a.color = yellow;

    Flock b = Flock();
    b.color = blue;

    Flock c = Flock();
    c.color = purple;

    Flock d = Flock();
    d.color = pink;

    Flock e = Flock();
    e.color = green;

    Flock f = Flock();
    f.color = red;

    Flock g = Flock();
    g.color = white;

    // add all flocks
    flockList.push_back(a);
    flockList.push_back(b);
    flockList.push_back(c);
    flockList.push_back(d);
    flockList.push_back(e);
    flockList.push_back(f);
    flockList.push_back(g);

    return flockList;
}

void Scene::executeScene()
{

    GLFWwindow *window;

    if (glfwInit() == 0)
    {
        exit(EXIT_FAILURE);
    }

    window = glfwCreateWindow(width, height, "Vincent Fugnitto - Boids!", nullptr, nullptr);

    if (window == nullptr)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);

    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    std::vector<Flock> flockList = initializeFlock();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, height, 0, 1, -1);
    glMatrixMode(GL_MODELVIEW);
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    while (glfwWindowShouldClose(window) == 0)
    {

        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(windowColor.r, windowColor.g, windowColor.b, windowColor.a);

        // create flocking task
        tbb::task_group flockTask;
        for (auto &flock : flockList)
        {
            flockTask.run([&] { flock.runFlock(); });
        }

        // synchronize all flocks
        flockTask.wait();

        // render flocks to screen
        for (auto &flock : flockList)
        {
            renderFlock(flock);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

float toRadians(float degrees)
{
    return static_cast<float>(degrees * (pi / 180.0));
}

void Scene::render(Boid boid, Color color)
{

    float radians = boid.velocity.heading() + toRadians(270);
    float degrees = (radians * (180 / pi));

    glPushMatrix();
    glTranslatef(boid.location.x, boid.location.y, 0);
    glRotatef(degrees, 0.0, 0.0, 1.0);
    glTranslatef(-boid.location.x, -boid.location.y, 0);

    glBegin(GL_TRIANGLES);
    glColor4f(color.r, color.g, color.b, color.a);
    glVertex2f(boid.location.x, boid.location.y + 5.5f);
    glVertex2f(boid.location.x + 2.5f, boid.location.y - 5.5f);
    glVertex2f(boid.location.x - 2.5f, boid.location.y - 5.5f);
    glEnd();

    glPopMatrix();
}

void Scene::renderFlock(Flock flock)
{
    for (auto &boid : flock.boids)
    {
        render(boid, flock.color);
    }
}

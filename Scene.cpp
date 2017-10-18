#include "Scene.h"

void Scene::executeScene() {

    GLFWwindow *window;

    if (!glfwInit())
        exit(EXIT_FAILURE);

    window = glfwCreateWindow(width, height, "Vincent Fugnitto - Boids!", nullptr, nullptr);

    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);

    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, height, 0, 1, -1);
    glMatrixMode(GL_MODELVIEW);
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    while (!glfwWindowShouldClose(window)) {

        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(windowColor.r, windowColor.g, windowColor.b, windowColor.a);

        a.run(a.color);
        b.run(b.color);
        c.run(c.color);
        d.run(d.color);
        e.run(e.color);
        f.run(f.color);
        g.run(g.color);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
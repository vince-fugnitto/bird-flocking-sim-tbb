#include "Scene.h"

void Scene::executeScene() {

    GLFWwindow *window;
    SceneController controller;

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

    std::vector<Flock> flockList = controller.initializeFlock();

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

        // controller.runScene(flockList);
        flockList[0].runFlock(flockList[0].color);
        flockList[1].runFlock(flockList[1].color);
        flockList[2].runFlock(flockList[2].color);
        flockList[3].runFlock(flockList[3].color);
        flockList[4].runFlock(flockList[4].color);
        flockList[5].runFlock(flockList[5].color);
        flockList[6].runFlock(flockList[6].color);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}


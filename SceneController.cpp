#include "SceneController.h"

std::vector<Flock> SceneController::initializeFlock() {

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
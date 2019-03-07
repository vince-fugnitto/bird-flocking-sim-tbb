# Boids: Bird Flocking Algorithm Simulation

--- 

### Description
Bird flocking program simulating the flocking behavior of birds following three algorithm rules:
1. **Separation**: steer to avoid crowding neighbor birds.
2. **Alignment**:  steer towards the average local leader.
3. **Cohesion**:   steer towards average position of local birds.

---

### Prerequisites

#### Ubuntu:

```console
sudo apt install libtbb-dev # install required tbb files
sudo apt install install libglfw3-dev # install required glfw files
```

---

#### Build Instructions:

```console
mkdir build # create a build directory
```

```console
cd build # enter build directory
```

``` console
cmake ../ # generate build files
```

```console
make # build the project
```

```console
./Boids_ # run the program
```






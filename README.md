# n-body-simulation

N-body simulation via octree estimation coded in C++ and OpenGL

# Overview

This project presents a simulation of gravitational bodies in space, each contributing to gravitational forces on the rest of the bodies.

N-body simulations are a classic example of how poorly-scaling algorithms can be optimized through clever structuring and estimation of data. As the number of bodies (n) becomes large, the time needed to simulate the changing position of each body increases at a rate proportional to n2.

# Algorithm Improvements

This particular implementation of the simulation improves this rate by structuring the data in a tree representing divisions of physical space. An octree is particularly useful for this purpose, as one octant of space relative to the 3D bounds of a parent node can be represented as one of the eight child nodes.

Structuring the data in this way allows us to store center-of-mass information for each node in the tree, and therefore, to use a high-level center-of-mass to represent the combination of many bodies.

The algorithm implemented in this project is the [Barnes-Hut Algorithm](https://en.wikipedia.org/wiki/Barnes%E2%80%93Hut_simulation), which takes the size of a high-level node and the distance between a particular body and the node's center of mass into account when determining whether to use the node's center of mass in the calculation, rather than recursively moving into the node and performing the calculation for child nodes.

# Simulation Parameters (Defined in Main.h)

NUMBER_OF_BODIES: The number of bodies in the system

CHEAT_RATIO: The value of Ɵ in the Barnes-Hut Algorithm (Explained below)

# Controls

* W – Move camera forward
* S – Move camera backward
* A – Move camera to the left
* D – Move camera to the right
* Q – Turn camera to the left
* E – Turn camera to the right
* Space – Move camera up
* Shift – Move camera down
* T – Toggle afterimages

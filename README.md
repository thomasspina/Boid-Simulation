# Boid simulation

This project showcases a boid simulation that reproduces the flocking behavior of groups of independent agents, similar to how birds behave in groups. Based on the paper written by Craig Reynolds, each individual agent, or "boid," is influenced by three main principles: separation, alignment, and cohesion. By adhering to these principles, the behavior of every individual boid can build up to form realistic and fluid flock behavior.

Through our simulation, users can experiment with and adjust the boids' behaviors to observe how these changes may affect the way flocks behave.

## Install
### MacOS

To run this program on MacOS you need to have XCode Command line tools installed
~~~
xcode-select --install
~~~

Then install CMake using Homebrew (https://brew.sh)
~~~
brew install cmake
~~~

Then clone the github repo onto your computer
~~~
git clone https://github.com/thomasspina/Boid-Simulation.git
~~~

In the repo make a build directory in which the project will be built and switch to that directory
~~~
mkdir build && cd ./build
~~~

From within this build directory you can build the project using cmake and make with the following command
~~~
cmake .. && make -j 4
~~~

Then to run the project you have to run the generated binary in the bin directory in the build directory
~~~
./bin/Boid-Simulation
~~~

### Windows

To be written


## Features

To be Written


## Technology

C++ was chosen to be the building blocks for the project because of the importance of performance within the simulation. To ensure we can display as many boids as possible while maintaining graphic fluidity, we aimed to make every single line of code in our project minimal and optimized. Likewise, C++ offers both performance and readibility, making it the perfect language for this project.

## Optimization

Considering that our simulation can spawn up to 1,000 boids at a time, time complexity is a major priority to ensure proper performance. Like any early prototype, our project started with a naive implementation. Since we had brute force, individual boids required information from every other boid on the screen, making our initial time complexity O(n²). Unsurprisingly, this was terrible, as 1,000 boids would require up to 10^3000 checks—enough to fry my laptop. 

To deal with this issue, we decided to try spatial partitioning using grids. By tracking the movements of boids using a grid system, we are able to cut down our checks by only checking neighbor boids in the cells closest to our current boid. This brings down our average time complexity to O(n) since each boid will only have to check neighbors in nearby cells.

## Future Improvements

Potential future improvements will still focus on optimization. Although grids reduce a significant amount of time complexity, the worst case can still reach O(n²). Considering the scenario where separation values are removed and alignment and cohesion are maximized, all 1,000 boids may end up in a single clump. In this case, our program will suffer, as all boids could occupy a single cell, resulting in O(n²) checks.

To address this, a more complex spatial partitioning method may be required: quadtrees. By recursively creating smaller cells, each boid can find much closer neighbors without suffering from extensive checks. In this case, we can modify each boid to check the 10 closest neighbors to itself instead of every boid within its vicinity. Since, in real life, birds only check their closest neighbors, this improvement would enhance both the behavioral accuracy relative to real-life agents and vastly improve our simulation performance.



# Boid simulation

This project showcases a boid simulation that reproduces the flocking behavior of groups of independent agents, similar to how birds behave in groups. Based on the paper written by Craig Reynolds, each individual agent, or "boid," is influenced by three main principles: separation, alignment, and cohesion. By adhering to these principles, the behavior of every individual boid can build up to form realistic and fluid flock behavior.

Through our simulation, users can experiment with and adjust the boids' behaviors to observe how these changes may affect the way flocks behave.

[Watch the Boid Simulation on YouTube](https://www.youtube.com/watch?v=DOgMToYF_0U&ab_channel=YchengLi)

## Navigation
- [Features](#features)
  - [Neighbourhood](#neighbourhood)
  - [Wandering](#wandering)
  - [Grid and Screen Boundaries](#grid-and-screen-boundaries)
  - [Avoid Mouse](#avoid-mouse)
  - [Rules](#rules)
- [Installation](#installation)
  - [MacOS](#macos)
  - [Windows](#windows)
    - [MinGW](#for-mingw)
    - [Visual Studio](#for-visual-studio)
    <!-- - [Ninja](#for-ninja) -->
- [Technology](#technology)
- [Optimization](#optimization)
- [Future Improvements](#future-improvements)
- [Sources](#sources)

## Features

The project has many adjustable parameters as seen from the boid menu.
<img width="1719" alt="Screenshot 2024-12-30 at 4 17 39 PM" src="https://github.com/user-attachments/assets/9a366667-e419-49c8-8e25-a17abad6ac5c" />
There are performance trackers at the very top, a configuration menu which handles basic simulation settings, and a rules menu which handles the weights attributed to each boid rule from the Cornell paper in the sources section. Most settings are self explanatory, for example there is a `Number of Boids` slider which adjusts the number of boids in the simulation (1000 boids should drop the framerate). Below are the less obvious settings.
#### Neighbourhood
You can show the neighbourhood in which the boids look for their flock neighbours using the `Show Boid Neighbourhood` checkbox. This neighbourhood radius is adjustable via the `Neighbourhood` slider.
![neighbourhood](https://github.com/user-attachments/assets/74e32f1a-fcc0-4372-9a0c-49e503236bd5)
#### Wandering
For the boids to look more natural there is a wander factor in the boid movement calculation that is indepedent of its neighbours. This wander factor adds randomness to boid and flock movements. This factor can be adjusted using the `Wander Factor` slider and can be enabled or disabled with the `Enable Boid Wandering` checkbox.
#### Grid and Screen Boundaries
Boids get warped to the other side of the screen upon reaching the edge of the screen by default. This behaviour can be changed using the `Avoid Screen Boundary` checkbox. There is also a checkbox named `Grid` which is used to overlay a grid on the display. This grid is part of the optimization where boids will only look for boids in neighbouring grid cells to check if they are in their neighbourhood radius. 
![avoid](https://github.com/user-attachments/assets/e2202adc-15b7-46e3-ac2c-d240da947dc2)
#### Avoid mouse
The `Enable Mouse Avoidance (Hold L-click)` checkbox enables or disables mouse avoidance. The boids will avoid the mouse if its near them and the user is left-clicking.
![mouse](https://github.com/user-attachments/assets/800f8a67-2cb4-4f44-8f35-b70ad8ca5dcc)
#### Rules 
The three rules explained in the Cornell paper in the sources can be toyed with using the three sliders and corresponding checkboxes in the menu. Very briefly the rules are:
* Separation: the boids avoid eachother
* Alignment: the boids head towards the same direction when in the same flock
* Cohesion: the boids move towards the center of the flock

## Installation
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

Then to run the project you have to run the generated binary in the bin directory within the build directory
~~~
./bin/Boid-Simulation
~~~

### Windows

Install Cmake (PATH recommended) (https://cmake.org/download/)

Then clone the github repo onto your computer
~~~
git clone https://github.com/thomasspina/Boid-Simulation.git
~~~

#### Choose one of the following toolchains:
  - **MinGW**: Install via [MSYS2](https://www.msys2.org/) or the standalone MinGW installer.
  - **Visual Studio**: Install Visual Studio 2019+ with "Desktop Development with C++" workload.
  <!-- - **Ninja**: Download Ninja from [ninja-build.org](https://ninja-build.org/). -->

Within the root directory, run the following commands based on the chosen toolchain:

#### For MinGW
~~~
cmake -S . -B build -G "MinGW Makefiles"
mingw32-make -C build
~~~

#### For Visual Studio
~~~
cmake -S . -B build -G "Visual Studio 17 2022"
msbuild build/Boid-Simulation.sln /p:Configuration=Release
~~~

<!-- #### For Ninja
~~~
cmake -S . -B build -G "Ninja"
ninja -C build
~~~ -->

#### Lastly

Run the generated binary in the bin directory within the build directory
~~~
./bin/Boid-Simulation
~~~

## Technology

C++ was chosen to be the building blocks for the project because of the importance of performance within the simulation. To ensure we can display as many boids as possible while maintaining graphic fluidity, we aimed to make every single line of code in our project minimal and optimized. Likewise, C++ offers both performance and readibility, making it the perfect language for this project.

## Optimization

Considering that our simulation can spawn up to 1,000 boids at a time, time complexity is a major priority to ensure proper performance. Like any early prototype, our project started with a naive implementation. Since we had brute force, individual boids required information from every other boid on the screen, making our initial time complexity O(n²). Unsurprisingly, this was terrible, as 1,000 boids would require up to 10^3000 checks—enough to fry my laptop. 

To deal with this issue, we decided to try spatial partitioning using grids. By tracking the movements of boids using a grid system, we are able to cut down our checks by only checking neighbor boids in the cells closest to our current boid. This brings down our average time complexity to O(n) since each boid will only have to check neighbors in nearby cells.

## Future Improvements

Potential future improvements will still focus on optimization. Although grids reduce a significant amount of time complexity, the worst case can still reach O(n²). Considering the scenario where separation values are removed and alignment and cohesion are maximized, all 1,000 boids may end up in a single clump. In this case, our program will suffer, as all boids could occupy a single cell, resulting in O(n²) checks.

To address this, a more complex spatial partitioning method may be required: quadtrees. By recursively creating smaller cells, each boid can find much closer neighbors without suffering from extensive checks. In this case, we can modify each boid to check the 10 closest neighbors to itself instead of every boid within its vicinity. Since, in real life, birds only check their closest neighbors, this improvement would enhance both the behavioral accuracy relative to real-life agents and vastly improve our simulation performance.

## Sources
https://www.red3d.com/cwr/boids/ - Our project is based on the boids written within Craig Reynolds's article.

https://people.ece.cornell.edu/land/courses/ece4760/labs/f2021/lab2boids/Boids-predator.html#Speed-limits - Our boids' logic is inspired by the implementations detailed in the Cornell ECE 4760 course resources.


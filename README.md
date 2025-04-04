# Simulating Flocking Behaviour With Boids Algorithm and OpenGL
<img src=imgs/t1.png width=40% style="margin:0px 10px"><img src=imgs/t2.png width=40% style="margin:0px 10px">

### Requirements
- CMake >= 3.2
- [OpenGL](https://www.khronos.org/opengl/wiki/Getting_Started#Downloading_OpenGL)
    - [GLFW](https://www.glfw.org/)
    - [GLEW](https://glew.sourceforge.net/install.html) 
    - [glm](https://github.com/g-truc/glm) (header-only library for math with vectors/matrices in OpenGL)
```
sudo apt-get install libglew-dev libglfw3-dev libglm-dev
```

### Compile and Run
```
make && ./flocksim
```

## Inspiration

Inspired by a recent article published by National Geographic, [What are birds doing when they fly in swarms? Scientists may now know.](https://www.nationalgeographic.com/photography/article/starling-birds-flock-cloud):

>The team has learned that no matter how large the flock, each starling interacts with only seven neighbors, which might be as much as their brains can handle. The exact neighbors change from second to second, but the starlings don’t track these shifting alliances. They merely fly in the same direction as whichever seven birds are nearest, while staying close but not too close. Alignment, attraction, and avoidance: By plugging this trio of rules into a computer model, along with some basic aerodynamics, Charlotte Hemelrijk from the University of Groningen in the Netherlands created a virtual murmuration that resembled the real deal—and matched the data from Rome.

>This showed that the starlings need no overarching plan, no leader, and no telepathic hive mind. They barely need to communicate at all. Through the simplest of interactions, playing out over distances of a few feet, the breathtaking, sky-spanning complexity of a murmuration emerges.


## Implementation

The implementation is based on the **Boids algorithm** to simulate flocking behavior. Boids are simulated with three core behaviors:

- **Alignment**: Each boid aligns its direction with neighbouring boids.
- **Attraction**: Each boid moves toward the center of mass of neighbouring boids.
- **Avoidance**: Each boid avoids collisions with nearby boids.

Each boid is represented as a triangle with colour given by its velocity. The boids appear to move in unison without any centralized control.


## References:
- [Ben Eater's Boids algorithm demonstration](https://github.com/beneater/boids)
- [V. Hunter Adams' explanation of the Boid's algorithm](https://vanhunteradams.com/Pico/Animal_Movement/Boids-algorithm.html)
